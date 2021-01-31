#include "LogAnalyserLib/LogAnalyserLib.h"
#include <iostream>
#include <string_view>
#include <future>

using namespace LogAnalyserLib;

void DoAggregationTask(DataMerger& merger, std::string_view filePath)
{
	ConsoleAppLogger::LogMessage("Analyzing a file: {}...", filePath);
	LogReader reader;
	reader.OpenFile(filePath);
	merger.AddDataToMerge(PlayerInfoAnalyser::AggregateData(reader.ReadData()));
	reader.CloseFile();
}

void ExecuteTasks(CommandLineParser& parser, DataMerger& merger)
{
	const auto workDirectory{parser.GetLogDirectory()};
	const auto numberOfFiles{parser.GetNumberOfFilesInDirectory()};
	const auto numberOfActiveThreads{parser.GetNumberOfThreads()};

	ConsoleAppLogger::LogMessage("Executing tasks: working directory: '{}', number of files: {}, number of threads: {}", workDirectory, numberOfFiles, numberOfActiveThreads);

	std::list<std::future<void>> taskList;
	size_t numberOfAnalysedFiles{0};
	size_t numberOfCurrentFile{0};

	while (numberOfAnalysedFiles < numberOfFiles)
	{
		if (taskList.size() < numberOfActiveThreads)
		{
			taskList.emplace_back(std::async(std::launch::async, DoAggregationTask, std::ref(merger), workDirectory + "\\file" + std::to_string(++numberOfCurrentFile) + ".log"));
			continue;
		}

		taskList.remove_if([&](auto& futureObj)
		{
			if (futureObj.valid())
			{
				futureObj.get();
				++numberOfAnalysedFiles;
				return true;
			}

			return false;
		});
	}
}

int main(int argc, char** argv)
try
{
	ConsoleAppLogger::LogMessage("Starting the log analyser...");
	CommandLineParser parser;
	DataMerger merger;

	parser.Parse(argc, argv);
	ExecuteTasks(parser, merger);

	ResultWriter resultWriter;
	resultWriter.OpenFile(parser.GetLogDirectory() + "\\agr.log");
	resultWriter.WriteDataToFile(merger.GetMergedDataCollection());
	resultWriter.CloseFile();

	ConsoleAppLogger::LogMessage("All task are completed. The application is finished.");

	return 0;
}
catch (const std::exception& ex)
{
	ConsoleAppLogger::LogMessage("Error has been occured: '{}'", ex.what());
	return -1;
}