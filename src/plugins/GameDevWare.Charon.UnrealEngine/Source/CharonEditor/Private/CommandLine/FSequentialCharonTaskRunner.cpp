#include "FSequentialCharonTaskRunner.h"

#include "Async/Async.h"

DEFINE_LOG_CATEGORY(LogFSequentialCharonTaskRunner);


FSequentialCharonTaskRunner::FSequentialCharonTaskRunner(const TArray<TSharedRef<ICharonTask>>& Tasks)
	: DispatchThread(ENamedThreads::AnyThread), TaskList(Tasks), CurrentTaskIndex(-1) 
{
	DisplayName = FText::Format(INVTEXT("Tasks [{0}]"), TaskList.Num());
}

bool FSequentialCharonTaskRunner::Run(ENamedThreads::Type EventDispatchThread)
{
	int32 Expected = -1;
	if (!CurrentTaskIndex.compare_exchange_strong(Expected, 0))
	{
		UE_LOG(LogFSequentialCharonTaskRunner, Warning, TEXT("Unable to run batched tasks because they are already running or finished."));
		return false;
	}

	DispatchThread = EventDispatchThread;
	BroadcastEvent(AsWeak(), TaskStart, DispatchThread);
	
	RunTask(0);
	return true;
}

void FSequentialCharonTaskRunner::RunTask(int32 TasksIndex)
{
	if (TasksIndex >= TaskList.Num()) // it was last task
	{
		BroadcastEvent(AsWeak(), TaskSucceed, DispatchThread);
		return;
	}
	
	const auto Task = TaskList[TasksIndex];
	const auto WeakThisPtr = this->AsWeak();
	const auto NextTaskFn = [WeakThisPtr, this]
	{
		const auto ThisPtr = WeakThisPtr.Pin();
		if (!ThisPtr.IsValid()) { return; }

		const int32 NextIndex = CurrentTaskIndex.fetch_add(1) + 1;
		if (NextIndex < 0)
		{
			return; // Stopped
		}
		RunTask(NextIndex);
	};
	
	Task->OnSucceed().AddLambda(NextTaskFn);
	Task->OnFailed().AddLambda(NextTaskFn);

	if (!Task->Run(DispatchThread))
	{
		UE_LOG(LogFSequentialCharonTaskRunner, Warning, TEXT("Batched task #%d '%s' has failed to start."), TasksIndex, *Task->GetDisplayName().ToString());
		NextTaskFn();
	}
	else
	{
		UE_LOG(LogFSequentialCharonTaskRunner, Verbose, TEXT("Running batched task #%d '%s'..."), TasksIndex, *Task->GetDisplayName().ToString());
	}
}


void FSequentialCharonTaskRunner::Stop()
{
	const int32 CurrentIndex = CurrentTaskIndex.exchange(INT32_MIN);
	if (CurrentIndex < 0 || CurrentIndex >= TaskList.Num())
	{
		return; // already done
	}
	
	TaskList[CurrentIndex]->Stop();
	BroadcastEvent(AsWeak(), TaskFailed, DispatchThread);
}

TSharedRef<ICharonTask> ICharonTask::AsSequentialRunner(const TArray<TSharedRef<ICharonTask>>& Tasks)
{
	return MakeShared<FSequentialCharonTaskRunner>(Tasks);
}
