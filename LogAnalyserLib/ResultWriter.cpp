#include "pch.h"
#include "ResultWriter.h"
#include <chrono>
#include <ctime>
#include <iomanip>

namespace LogAnalyserLib {

ResultWriter::~ResultWriter()
{
	CloseFile();
}

void ResultWriter::OpenFile(std::string_view outFile)
{
	resultWriter.open(outFile.data(), std::ifstream::out);

	if (!resultWriter.is_open())
	{
		throw std::runtime_error(std::string("Can't open a file: ").append(outFile));
	}
}

void ResultWriter::CloseFile()
{
	if (resultWriter.is_open())
	{
		resultWriter.close();
	}
}

void ResultWriter::WriteDataToFile(const AggregatedDataList& agrCollection)
{
	resultWriter << "===== Aggregated logs =====" << std::endl << std::endl;
	
	for (const auto& dataElem : agrCollection)
	{
		std::time_t t = dataElem.info.ts_fact;
		const auto timeDescr{std::put_time(gmtime(&t), "%c")};

		resultWriter << "UTC: " << timeDescr << "; fact_name: " << dataElem.info.fact_name << "; " << dataElem.info.props << "; an action occurred: " << dataElem.eventCounter << " times." << std::endl;
	}
}

}