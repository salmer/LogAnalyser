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
		numberOfFiles = ParseNumber(argValue);
		break;
	case CommandLineArguments::NumberOfThreads:
		numberOfThreads = ParseNumber(argValue);
		break;

	default:
		throw std::runtime_error("Error: Unknown command line argument");
	}
}

size_t CommandLineParser::ParseNumber(const char* strArg) const
{
	const auto number{std::stoi(strArg)};
	if (number < 0)
	{
		throw std::runtime_error("Error: Negative number was set: value < 0");
	}

	return number;
}

void CommandLineParser::ValidateMandatoryParameters() const
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

size_t CommandLineParser::GetNumberOfFilesInDirectory() const
{
	return numberOfFiles;
}

size_t CommandLineParser::GetNumberOfThreads() const
{
	return numberOfThreads;
}

}