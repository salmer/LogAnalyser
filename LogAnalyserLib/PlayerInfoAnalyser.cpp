#include "pch.h"
#include "PlayerInfoAnalyser.h"

namespace LogAnalyserLib {

AggregatedDataList PlayerInfoAnalyser::AggregateData(const PlayerActionInfoList& playerInfoSet)
{
	AggregatedDataList aggregatedData;

	for (const auto& playerInfo : playerInfoSet)
	{
		const auto iter{FindElement(aggregatedData, playerInfo)};
		if (iter == aggregatedData.end())
		{
			aggregatedData.emplace_back(AggregatedActionData{playerInfo, 1});
			continue;
		}

		iter->eventCounter++;
	}

	return aggregatedData;
}



}