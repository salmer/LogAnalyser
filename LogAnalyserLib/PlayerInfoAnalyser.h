#pragma once

#include "PlayerActionInfo.h"
#include <map>

namespace LogAnalyserLib {



class PlayerInfoAnalyser
{
public:
	AggregatedDataList AggregateData(const PlayerActionInfoList& playerInfoSet);

private:
	AggregatedDataList::iterator FindElement(AggregatedDataList& aggregatedDataList, const PlayerActionInfo& playerInfo) const;
};

}