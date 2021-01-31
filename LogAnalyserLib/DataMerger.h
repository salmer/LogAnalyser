#pragma once

#include <condition_variable>
#include <future>
#include <queue>
#include "PlayerActionInfo.h"

namespace LogAnalyserLib {

class DataMerger
{
public:
	DataMerger();
	~DataMerger();

	void AddDataToMerge(AggregatedDataList&& dataChunk);
	const AggregatedDataList& GetMergedDataCollection();

private:
	void StartMergeTask();
	void StopMergeTask();
	void WaitTaskIsFinished();
	void MergeTask();
	void UpdateTaskState();
	void HandleTaskState();
	AggregatedDataList ExtractAggregatedDataChunk();
	void AggregateData(const AggregatedDataList& dataChunk);

	std::queue<AggregatedDataList> dataQueue;
	AggregatedDataList aggregatedCollection;

	enum class DataMergerState
	{
		Pending,
		Running,
	};

	std::atomic_bool taskIsRunning;
	std::atomic<DataMergerState> taskState;
	std::future<void> mergeTask;
	std::mutex dataLocker;
};

}