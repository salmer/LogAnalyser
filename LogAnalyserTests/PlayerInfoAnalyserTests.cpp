#include "pch.h"
#include "LogAnalyserLib/LogAnalyserLib.h"
#include "TestData.h"


namespace LogAnalyserLib { namespace Testing {

TEST(PlayerInfoAnalyserTests, Analyser_returns_empty_list_if_no_input_data)
{
	const PlayerActionInfoList testList;

	const auto aggregatedData{PlayerInfoAnalyser::AggregateData(testList)};
	EXPECT_TRUE(aggregatedData.empty());
}

TEST(PlayerInfoAnalyserTests, Analyser_can_aggregate_input_data)
{
	const PlayerActionInfoList playerActionTestList{firstTestInfo, firstTestInfo, secondTestInfo, thirdTestInfo, firstTestInfo,
		firstTestInfo, fourthTestInfo, fourthTestInfo, fifthTestInfo, fifthTestInfo, fifthTestInfo};

	const auto aggregatedData{PlayerInfoAnalyser::AggregateData(playerActionTestList)};

	// Expected results of an aggregation.
 	ASSERT_EQ(aggregatedData.size(), 5);

	const auto iterBegin{aggregatedData.begin()};
	ASSERT_EQ(iterBegin->eventCounter, 4);
	ASSERT_EQ(std::next(iterBegin, 1)->eventCounter, 1);
	ASSERT_EQ(std::next(iterBegin, 2)->eventCounter, 1);
	ASSERT_EQ(std::next(iterBegin, 3)->eventCounter, 2);
	ASSERT_EQ(std::next(iterBegin, 4)->eventCounter, 3);
}

}}