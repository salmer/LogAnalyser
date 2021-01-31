#include "pch.h"
#include "LogAnalyserLib/LogAnalyserLib.h"
#include "TestData.h"

namespace LogAnalyserLib { namespace Testing {

TEST(DataMergerTests, Merger_can_aggregate_data_collection)
{
	AggregatedDataList testList{{firstTestInfo, 10}, {secondTestInfo, 4}, {thirdTestInfo, 7}, {fourthTestInfo, 14}, {fifthTestInfo, 35}};
	DataMerger merger;

	constexpr auto countDataAdded{10};
	for (int i = 0; i < countDataAdded; ++i)
	{	
		merger.AddDataToMerge(std::move(testList));
	}

	const auto agrCollection{merger.GetMergedDataCollection()};
	ASSERT_EQ(agrCollection.size(), testList.size());
	
	for (size_t i = 0; i < agrCollection.size(); ++i)
	{
		ASSERT_EQ(agrCollection[i].eventCounter, testList[i].eventCounter * countDataAdded);
	}
}

}}
