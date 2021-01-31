#pragma once

#include "pch.h"
#include "PlayerActionInfo.h"

namespace LogAnalyserLib {

bool operator==(const PlayerActionInfo& first, const PlayerActionInfo& second)
{
	return first.ts_fact == second.ts_fact
		&& first.fact_name == second.fact_name
		&& std::equal(first.props.begin(), first.props.end(), second.props.begin());
}

AggregatedDataList::iterator FindElement(AggregatedDataList& aggregatedDataList, const PlayerActionInfo& playerInfo)
{
	const auto iter = std::find_if(aggregatedDataList.begin(), aggregatedDataList.end(), [playerInfo](const auto& agregElem)
	{
		return agregElem.info == playerInfo;
	});

	return iter;
}

}