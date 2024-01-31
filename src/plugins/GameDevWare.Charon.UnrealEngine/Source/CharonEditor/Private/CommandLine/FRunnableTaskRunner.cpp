#include "FRunnableTaskRunner.h"

#include "Async/Async.h"

DEFINE_LOG_CATEGORY(LogFRunnableTaskRunner);

FRunnableTaskRunner::FRunnableTaskRunner(const TSharedRef<FRunnable>& Runnable, const FText& DisplayName, ENamedThreads::Type RunThread)
	: DisplayName(DisplayName), EventThread(ENamedThreads::AnyThread), RunThread(RunThread), Runnable(Runnable)
{
}

bool FRunnableTaskRunner::Start(ENamedThreads::Type EventDispatchThread)
{
	ERunStatus ExpectedReady = ERunStatus::Ready;
	if (!RunStatus.compare_exchange_strong(ExpectedReady, ERunStatus::Running))
	{
		UE_LOG(LogFRunnableTaskRunner, Warning, TEXT("Unable to run delegate task because it is already running or finished."));
		return false;
	}

	EventThread = EventDispatchThread;
	BroadcastEvent(AsWeak(), TaskStart, EventThread);
	
	ERunStatus ExpectedRunning = ERunStatus::Running;
	if (!Runnable->Init())
	{
		UE_LOG(LogFRunnableTaskRunner, Warning, TEXT("Unable to run FRunnable task because it is failed to initialize."));

		if (RunStatus.compare_exchange_strong(ExpectedRunning, ERunStatus::Failed))
		{
			BroadcastEvent(AsWeak(), TaskFailed, EventThread);
		}
		return false;
	}
	
	if (RunThread == ENamedThreads::AnyThread)
	{
		const auto ExitCode = Runnable->Run();
		OnRunnableExited(ExitCode);
	}
	else
	{
		const auto WeakThisPtr = this->AsWeak();
		AsyncTask(RunThread, [WeakThisPtr, this]
		{
			const auto ThisPtr = WeakThisPtr.Pin();
			if (!ThisPtr.IsValid()) { return; }
			
			const auto ExitCode = Runnable->Run();
			OnRunnableExited(ExitCode);
		});
	}

	return true;
}

void FRunnableTaskRunner::OnRunnableExited(uint32 ExitCode)
{
	UE_LOG(LogFRunnableTaskRunner, Log, TEXT("FRunnable exited with code %d. Any exit code except 0 is considered a failure."), ExitCode);

	ERunStatus ExpectedRunning = ERunStatus::Running;
	if (ExitCode == 0 && RunStatus.compare_exchange_strong(ExpectedRunning, ERunStatus::Succeed))
	{
		BroadcastEvent(AsWeak(), TaskSucceed, EventThread);
	}
	else if (ExitCode != 0 && RunStatus.compare_exchange_strong(ExpectedRunning, ERunStatus::Failed))
	{
		BroadcastEvent(AsWeak(), TaskFailed, EventThread);
	}
}

void FRunnableTaskRunner::Stop()
{
	ERunStatus ExpectedRunning = ERunStatus::Running;
	if (RunStatus.compare_exchange_strong(ExpectedRunning, ERunStatus::Stopped))
	{
		Runnable->Stop();
	}
}

TSharedRef<ICharonTask> ICharonTask::FromRunnable(const TSharedRef<FRunnable>& Runnable, const FText& DisplayName, ENamedThreads::Type RunThread)
{
	return MakeShared<FRunnableTaskRunner>(Runnable, DisplayName, RunThread);	
}