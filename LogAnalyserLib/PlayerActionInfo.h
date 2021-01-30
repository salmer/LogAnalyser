#pragma once

namespace LogAnalyserLib {

struct PlayerActionInfo
{
	uint32_t ts_fact;
	uint32_t actor_id;
	std::string fact_name;
	std::map<std::string, uint32_t> props;
};

}