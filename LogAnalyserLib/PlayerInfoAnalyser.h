#pragma once

#include "PlayerActionInfo.h"
#include <map>

namespace LogAnalyserLib {

class PlayerInfoAnalyser
{
public:
	static AggregatedDataList AggregateData(const PlayerActionInfoList& playerInfoSet);
};

}