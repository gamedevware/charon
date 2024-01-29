#include "FDelegateTaskRunner.h"

#include "Async/Async.h"

DEFINE_LOG_CATEGORY(LogFDelegateTaskRunner);

FDelegateTaskRunner::FDelegateTaskRunner(const FSimpleDelegate& Delegate, const FText& DisplayName)
	: DisplayName(DisplayName), DispatchThread(ENamedThreads::AnyThread), Delegate(Delegate)
{
}

bool FDelegateTaskRunner::Run(ENamedThreads::Type EventDispatchThread)
{
	ERunStatus ExpectedReady = ERunStatus::Ready;
	if (!RunStatus.compare_exchange_strong(ExpectedReady, ERunStatus::Running))
	{
		UE_LOG(LogFDelegateTaskRunner, Warning, TEXT("Unable to run delegate task because it is already running or finished."));
		return false;
	}

	DispatchThread = EventDispatchThread;
	BroadcastEvent(AsWeak(), TaskStart, DispatchThread);
	
	ERunStatus ExpectedRunning = ERunStatus::Running;
	if (!Delegate.IsBound())
	{
		UE_LOG(LogFDelegateTaskRunner, Warning, TEXT("Unable to run delegate task because it not bound to a method."));

		if (RunStatus.compare_exchange_strong(ExpectedRunning, ERunStatus::Failed))
		{
			BroadcastEvent(AsWeak(), TaskFailed, DispatchThread);
		}
		return false;
	}
	
	if (DispatchThread == ENamedThreads::AnyThread)
	{
		Delegate.Execute();
		
		if (RunStatus.compare_exchange_strong(ExpectedRunning, ERunStatus::Succeed))
		{
			BroadcastEvent(AsWeak(), TaskSucceed, DispatchThread);
		}
	} else
	{
		const auto WeakThisPtr = this->AsWeak();
		AsyncTask(DispatchThread, [WeakThisPtr, this]
		{
			const auto ThisPtr = WeakThisPtr.Pin();
			if (!ThisPtr.IsValid()) { return; }
			
			Delegate.Execute();

			ERunStatus ExpectedRunning = ERunStatus::Running;
			if (RunStatus.compare_exchange_strong(ExpectedRunning, ERunStatus::Succeed))
			{
				BroadcastEvent(AsWeak(), TaskSucceed, DispatchThread);
			}
		});
	}

	return true;
}

void FDelegateTaskRunner::Stop()
{
	ERunStatus ExpectedRunning = ERunStatus::Running;
	RunStatus.compare_exchange_strong(ExpectedRunning, ERunStatus::Stopped);
}

TSharedRef<ICharonTask> ICharonTask::FromSimpleDelegate(const FSimpleDelegate& Delegate, const FText& DisplayName)
{
	return MakeShared<FDelegateTaskRunner>(Delegate, DisplayName);
}
