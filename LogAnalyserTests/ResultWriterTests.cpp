#include "pch.h"
#include "LogAnalyserLib/LogAnalyserLib.h"
#include "TestData.h"
#include <filesystem>

namespace LogAnalyserLib { namespace Testing {

TEST(ResultWriterTests, Result_writer_can_write_data_to_logs)
{
	const std::string file{"testFile.log"};
	const AggregatedDataList testList{{firstTestInfo, 10}, {secondTestInfo, 4}, {thirdTestInfo, 7}, {fourthTestInfo, 14}, {fifthTestInfo, 35}};

	ResultWriter writer;
	ASSERT_NO_THROW(writer.OpenFile(file));
	ASSERT_NO_THROW(writer.WriteDataToFile(testList));
	ASSERT_NO_THROW(writer.CloseFile());

	ASSERT_TRUE(std::filesystem::exists(file));
	ASSERT_GT(std::filesystem::file_size(file), 0);

	std::filesystem::remove(file);
}

}}