#pragma once

namespace LogAnalyserLib {

using PropsList = std::map<std::string, uint32_t>;

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


using PlayerActionInfoList = std::vector<PlayerActionInfo>;

using AggregatedDataList = std::vector<AggregatedActionData>;
AggregatedDataList::iterator FindElement(AggregatedDataList& aggregatedDataList, const PlayerActionInfo& playerInfo);

}