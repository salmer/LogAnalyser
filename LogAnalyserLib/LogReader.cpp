#include "pch.h"
#include "LogReader.h"
#include <string>

namespace LogAnalyserLib {

PlayerActionInfo GetPlayerActionInfoFromJson(nlohmann::json&& rawData)
{
	return {rawData["ts_fact"].get<uint32_t>(),
		rawData["actor_id"].get<uint32_t>(),
		rawData["fact_name"].get<std::string>(),
		rawData["props"].get<std::map<std::string, uint32_t>>()};
}


LogReader::~LogReader()
{
	CloseFile();
}

void LogReader::OpenFile(std::string_view filePath)
{
	logReader.open(filePath.data(), std::ifstream::in);

	if (!logReader.is_open())
	{
		throw std::runtime_error(std::string("Can't open a file: ").append(filePath));
	}
}

void LogReader::CloseFile()
{
	if (logReader.is_open())
	{
		logReader.close();
	}
}

std::vector<PlayerActionInfo> LogReader::ReadData()
{
	std::vector<PlayerActionInfo> listOfData;
	std::string lineBuffer;

	while (!logReader.eof())
	{
		std::getline(logReader, lineBuffer);
		if (lineBuffer.empty())
		{
			// Ignore empty lines in log files.
			continue;
		}

		const auto aggreagatedPlayerInfo{GetPlayerActionInfoFromJson(nlohmann::json::parse(lineBuffer))};
		listOfData.emplace_back(aggreagatedPlayerInfo);
	}

	return listOfData;
}

}