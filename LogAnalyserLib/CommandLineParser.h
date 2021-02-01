#pragma once

#include <string>

namespace LogAnalyserLib {

class CommandLineParser
{
public:
	CommandLineParser();

	void Parse(int argc, char** argv);

	const std::string& GetLogDirectory() const;
	size_t GetNumberOfFilesInDirectory() const;
	size_t GetNumberOfThreads() const;

private:
	void ValidateInputParams(int argc) const;
	void ParseCommandLine(int argc, char** argv);
	void HandleArgument(int index, char** argv);
	size_t ParseNumber(const char* strArg) const;
	void ValidateMandatoryParameters() const;

	std::string logDirectory;
	size_t numberOfFiles;
	size_t numberOfThreads;
};

}

