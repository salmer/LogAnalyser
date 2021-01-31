#include "pch.h"
#include "LogAnalyserLib/LogAnalyserLib.h"
#include "TestData.h"

namespace LogAnalyserLib { namespace Testing {

TEST(DataMergerTests, Merger_can_aggregate_sorted_data_collection_by_timestamp)
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
	
	ASSERT_EQ(agrCollection[0].eventCounter, testList[0].eventCounter * countDataAdded);
	ASSERT_EQ(agrCollection[1].eventCounter, testList[1].eventCounter * countDataAdded);
	ASSERT_EQ(agrCollection[2].eventCounter, testList[4].eventCounter * countDataAdded);
	ASSERT_EQ(agrCollection[3].eventCounter, testList[2].eventCounter * countDataAdded);
	ASSERT_EQ(agrCollection[4].eventCounter, testList[3].eventCounter * countDataAdded);
}

}}
