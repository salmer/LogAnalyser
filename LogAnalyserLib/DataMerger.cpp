#include "pch.h"
#include "DataMerger.h"

namespace LogAnalyserLib {

DataMerger::DataMerger()
	: taskIsRunning{false}
	, taskState{DataMergerState::Pending}
{
}

DataMerger::~DataMerger()
{
	StopMergeTask();
}

void DataMerger::StopMergeTask()
{
	taskIsRunning = false;
	WaitTaskIsFinished();
}

void DataMerger::AddDataToMerge(AggregatedDataList&& dataChunk)
{
	std::unique_lock lock(dataLocker);
	dataQueue.emplace(dataChunk);
	lock.unlock();

	StartMergeTask();
}

void DataMerger::StartMergeTask()
{
	if (taskIsRunning)
	{
		return;
	}

	WaitTaskIsFinished();
	taskIsRunning = true;
	mergeTask = std::async(std::launch::async, &DataMerger::MergeTask, this);
}

const AggregatedDataList& DataMerger::GetMergedDataCollection()
{
	WaitTaskIsFinished();

	aggregatedCollection.sort([](const auto& first, const auto& second)
	{
		return first.info.ts_fact < second.info.ts_fact;
	});

	return aggregatedCollection;
}

void DataMerger::WaitTaskIsFinished()
{
	if (mergeTask.valid())
	{
		mergeTask.get();
	}
}

void DataMerger::MergeTask()
{
	while (taskIsRunning)
	{
		UpdateTaskState();
		HandleTaskState();
	}
}

void DataMerger::UpdateTaskState()
{
	std::lock_guard lock(dataLocker);
	taskState = dataQueue.empty() ? DataMergerState::Pending : DataMergerState::Running;
}

void DataMerger::HandleTaskState()
{
	if (taskState == DataMergerState::Running)
	{
		const auto aggregatedDataChunk{ExtractAggregatedDataChunk()};
		AggregateData(aggregatedDataChunk);
	}

	if (taskState == DataMergerState::Pending)
	{
		taskIsRunning = false;
	}
}

AggregatedDataList DataMerger::ExtractAggregatedDataChunk()
{
	std::lock_guard lock(dataLocker);
	const auto aggregatedChunk{dataQueue.front()};
	dataQueue.pop();

	return aggregatedChunk;
}

void DataMerger::AggregateData(const AggregatedDataList& dataChunk)
{
	for (const auto& mergeElem : dataChunk)
	{
		const auto iter{FindElement(aggregatedCollection, mergeElem.info)};
		if (iter == aggregatedCollection.end())
		{
			aggregatedCollection.emplace_back(mergeElem);
			continue;
		}

		iter->eventCounter += mergeElem.eventCounter;
	}
}

}