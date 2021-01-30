#include "pch.h"
#include "LogAnalyserLib/LogAnalyserLib.h"


namespace LogAnalyserLib { namespace Testing {

TEST(PlayerInfoAnalyserTests, Analyser_returns_empty_list_if_no_input_data)
{
	PlayerActionInfoList testList;
	PlayerInfoAnalyser analyser;

	const auto aggregatedData{analyser.AggregateData(testList)};
	EXPECT_TRUE(aggregatedData.empty());
}

TEST(PlayerInfoAnalyserTests, Analyser_can_aggregate_input_data)
{
	const PlayerActionInfo firstTestInfo{86400, "name1",
		PropsList{{"prop1", 1}, {"prop10", 10}, {"prop9", 9}, {"prop8", 8}, {"prop7", 7},
		{"prop6", 6}, {"prop5", 5}, {"prop4", 4}, {"prop3", 3}, {"prop2", 2}}};

	const PlayerActionInfo secondTestInfo{86400, "name1",
		PropsList{{"prop1", 15}, {"prop10", 10}, {"prop9", 9}, {"prop8", 8}, {"prop7", 7},
		{"prop6", 6}, {"prop5", 5}, {"prop4", 4}, {"prop3", 3}, {"prop2", 2}}};

	const PlayerActionInfo thirdTestInfo{86500, "name1",
		PropsList{{"prop1", 1}, {"prop10", 10}, {"prop9", 9}, {"prop8", 8}, {"prop7", 7},
		{"prop6", 6}, {"prop5", 5}, {"prop4", 4}, {"prop3", 3}, {"prop2", 2}}};

	const PlayerActionInfo fourthTestInfo{86500, "name2",
		PropsList{{"prop1", 1}, {"prop10", 10}, {"prop9", 9}, {"prop8", 8}, {"prop7", 7},
		{"prop6", 6}, {"prop5", 5}, {"prop4", 4}, {"prop3", 3}, {"prop2", 2}}};

	const PlayerActionInfo fifthTestInfo{86400, "name2",
		PropsList{{"prop1", 1}, {"prop10", 10}, {"prop9", 9}, {"prop8", 8}, {"prop7", 7},
		{"prop6", 6}, {"prop5", 5}, {"prop4", 4}, {"prop3", 3}, {"prop2", 2}}};

	PlayerActionInfoList testList{firstTestInfo, firstTestInfo, secondTestInfo, thirdTestInfo, firstTestInfo, 
		firstTestInfo, fourthTestInfo, fourthTestInfo, fifthTestInfo, fifthTestInfo, fifthTestInfo};

	PlayerInfoAnalyser analyser;
	const auto aggregatedData{analyser.AggregateData(testList)};

	// Expected results of an aggregation.
 	ASSERT_EQ(aggregatedData.size(), 5);
	ASSERT_EQ(aggregatedData[0].eventCounter, 4);
	ASSERT_EQ(aggregatedData[1].eventCounter, 1);
	ASSERT_EQ(aggregatedData[2].eventCounter, 1);
	ASSERT_EQ(aggregatedData[3].eventCounter, 2);
	ASSERT_EQ(aggregatedData[4].eventCounter, 3);
}


}}