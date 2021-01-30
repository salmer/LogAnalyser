#pragma once

#include <string_view>
#include <fstream>
#include "PlayerActionInfo.h"

namespace LogAnalyserLib {

class LogReader
{
public:
	~LogReader();

	void OpenFile(std::string_view filePath);
	void CloseFile();
	PlayerActionInfoList ReadData();

private:
	std::ifstream logReader;
};

}