#include "pch.h"
#include "LogReader.h"
#include <string>

#include <rapidjson\document.h>
#include <rapidjson\pointer.h>
#include <rapidjson\filereadstream.h>

namespace LogAnalyserLib {

PlayerActionInfo GetPlayerActionInfoFromJson(const rapidjson::Document& data)
{
	return {data["ts_fact"].GetUint(),
		data["fact_name"].GetString(),
		{
			data["props"]["prop1"].GetUint(),
			data["props"]["prop2"].GetUint(),
			data["props"]["prop3"].GetUint(),
			data["props"]["prop4"].GetUint(),
			data["props"]["prop5"].GetUint(),
			data["props"]["prop6"].GetUint(),
			data["props"]["prop7"].GetUint(),
			data["props"]["prop8"].GetUint(),
			data["props"]["prop9"].GetUint(),
			data["props"]["prop10"].GetUint()
	}
	};
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

		rapidjson::Document data;
		data.Parse(lineBuffer.c_str());
		listOfData.emplace_back(GetPlayerActionInfoFromJson(data));
	}

	return listOfData;
}

}