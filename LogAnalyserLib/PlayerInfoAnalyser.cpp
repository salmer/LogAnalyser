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

AggregatedDataList::iterator PlayerInfoAnalyser::FindElement(AggregatedDataList& aggregatedDataList, const PlayerActionInfo& playerInfo) const
{
	const auto iter = std::find_if(aggregatedDataList.begin(), aggregatedDataList.end(), [playerInfo](const auto& agregElem)
	{
		if (agregElem.info.ts_fact == playerInfo.ts_fact 
			&& agregElem.info.fact_name == playerInfo.fact_name
			&& std::equal(agregElem.info.props.begin(), agregElem.info.props.end(), playerInfo.props.begin()))
		{
			return true;
		}

		return false;
	});

	return iter;
}

}