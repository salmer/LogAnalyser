#pragma once

#include <fstream>
#include <string_view>
#include "PlayerActionInfo.h"

namespace LogAnalyserLib {

class ResultWriter
{
public:
	~ResultWriter();

	void OpenFile(std::string_view outFile);
	void CloseFile();

	void WriteDataToFile(const AggregatedDataList& agrCollection);

private:
	std::ofstream resultWriter;
};

}