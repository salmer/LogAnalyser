#include "pch.h"
#include "CommandLineParser.h"
#include <sstream>
#include <string>

namespace LogAnalyserLib{

enum class CommandLineArguments
{
	LogsDirectory,
	NumberOfFiles,
	NumberOfThreads,
};

const std::map<std::string, CommandLineArguments> cmdParamsList{
	{"-d", CommandLineArguments::LogsDirectory},
	{"-n", CommandLineArguments::NumberOfFiles},
	{"-t", CommandLineArguments::NumberOfThreads}
};


CommandLineParser::CommandLineParser()
	: logDirectory{}
	, numberOfFiles{0}
	, numberOfThreads{1}
{}

void CommandLineParser::Parse(const int argc, char** argv)
{ 
	ValidateInputParams(argc);
	ParseCommandLine(argc, argv);
}

void CommandLineParser::ValidateInputParams(const int argc) const
{
	constexpr auto allowedArgPair{2};
	if ((argc - 1) % allowedArgPair != 0)
	{
		throw std::runtime_error("Error: Incorrect number of command line arguments.");
	}
}

void CommandLineParser::ParseCommandLine(const int argc, char** argv)
{
	constexpr auto offset{2};
	for (int idx = 1; idx < argc; idx += offset)
	{
		HandleArgument(idx, argv);
	}

	ValidateMandatoryParameters();
}

void CommandLineParser::HandleArgument(const int index, char** argv)
{
	const auto argKey{argv[index]};
	const auto argValue{argv[index + 1]};

	const auto expectedArgument{cmdParamsList.at(argKey)};
	switch (expectedArgument)
	{
	case CommandLineArguments::LogsDirectory:
		logDirectory = argValue;
		break;
	case CommandLineArguments::NumberOfFiles:
		numberOfFiles = std::stoi(argValue);
		break;
	case CommandLineArguments::NumberOfThreads:
		numberOfThreads = std::stoi(argValue);
		break;

	default:
		throw std::runtime_error("Error: Unknown command line argument");
	}
}

void CommandLineParser::ValidateMandatoryParameters()
{
	if (logDirectory.empty())
	{
		throw std::runtime_error("Mandatory argument is not set: 'log directory'.");
	}

	if (numberOfFiles == 0)
	{
		throw std::runtime_error("Mandatory argument is not set: 'number of files'.");
	}
}

const std::string& CommandLineParser::GetLogDirectory() const
{
	return logDirectory;
}

unsigned int CommandLineParser::GetNumberOfFilesInDirectory() const
{
	return numberOfFiles;
}

unsigned int CommandLineParser::GetNumberOfThreads() const
{
	return numberOfThreads;
}

}