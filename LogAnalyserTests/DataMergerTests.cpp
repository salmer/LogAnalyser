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

	const auto iterCollection{agrCollection.begin()};
	const auto iterTestList{testList.begin()};
	
	ASSERT_EQ(iterCollection->eventCounter, iterTestList->eventCounter * countDataAdded);
	ASSERT_EQ(std::next(iterCollection, 1)->eventCounter, std::next(iterTestList, 1)->eventCounter * countDataAdded);
	ASSERT_EQ(std::next(iterCollection, 2)->eventCounter, std::next(iterTestList, 4)->eventCounter * countDataAdded);
	ASSERT_EQ(std::next(iterCollection, 3)->eventCounter, std::next(iterTestList, 2)->eventCounter * countDataAdded);
	ASSERT_EQ(std::next(iterCollection, 4)->eventCounter, std::next(iterTestList, 3)->eventCounter * countDataAdded);
}

}}
