#pragma once

#include <ostream>
#include <vector>
#include <list>

namespace LogAnalyserLib {

using PropsList = std::vector<uint32_t>;
std::ostream& operator<< (std::ostream& os, const PropsList& props);

struct PlayerActionInfo
{
	uint32_t ts_fact;
	std::string fact_name;
	PropsList props;
};

struct AggregatedActionData
{
	PlayerActionInfo info;
	uint32_t eventCounter;
};


using PlayerActionInfoList = std::list<PlayerActionInfo>;

using AggregatedDataList = std::list<AggregatedActionData>;
AggregatedDataList::iterator FindElement(AggregatedDataList& aggregatedDataList, const PlayerActionInfo& playerInfo);

}