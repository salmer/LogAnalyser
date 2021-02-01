#include "pch.h"
#include "LogReader.h"
#include <string>

namespace LogAnalyserLib {

PlayerActionInfo GetPlayerActionInfoFromJson(nlohmann::json&& rawData)
{
	PlayerActionInfo actionInfo;
	actionInfo.ts_fact = rawData["ts_fact"].get<uint32_t>();
	actionInfo.fact_name = rawData["fact_name"].get<std::string>();
	actionInfo.props.resize(10);
	actionInfo.props =
	{
		rawData["props"]["prop1"].get<uint32_t>(),
		rawData["props"]["prop2"].get<uint32_t>(),
		rawData["props"]["prop3"].get<uint32_t>(),
		rawData["props"]["prop4"].get<uint32_t>(),
		rawData["props"]["prop5"].get<uint32_t>(),
		rawData["props"]["prop6"].get<uint32_t>(),
		rawData["props"]["prop7"].get<uint32_t>(),
		rawData["props"]["prop8"].get<uint32_t>(),
		rawData["props"]["prop9"].get<uint32_t>(),
		rawData["props"]["prop10"].get<uint32_t>(),
	};

	return actionInfo;
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

PlayerActionInfoList LogReader::ReadData()
{
	PlayerActionInfoList listOfData;
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