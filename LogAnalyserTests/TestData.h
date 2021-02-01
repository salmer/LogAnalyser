#pragma once


namespace LogAnalyserLib { namespace Testing {

const PlayerActionInfo firstTestInfo{86400, "name1", PropsList{1, 10, 9, 8, 7, 6, 5, 4, 3, 2}};
const PlayerActionInfo secondTestInfo{86400, "name1", PropsList{15, 10, 9, 8, 7, 6, 5, 4, 3, 2}};
const PlayerActionInfo thirdTestInfo{86500, "name1", PropsList{1, 10, 9, 8, 7, 6, 5, 4, 3, 2}};
const PlayerActionInfo fourthTestInfo{86500, "name2", PropsList{1, 10, 9, 8, 7, 6, 5, 4, 3, 2}};
const PlayerActionInfo fifthTestInfo{86400, "name2", PropsList{1, 10, 9, 8, 7, 6, 5, 4, 3, 2}};

}}