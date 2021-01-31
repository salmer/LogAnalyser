#pragma once


namespace LogAnalyserLib { namespace Testing {

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

}}