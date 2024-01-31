#pragma once

#include "GameData\ICharonTask.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFRunnableTaskRunner, Log, All);

class FRunnableTaskRunner : public TSharedFromThis<FRunnableTaskRunner>, public ICharonTask
{
private:
	enum class ERunStatus
	{
		Ready,
		Running,
		Stopped,
		Succeed,
		Failed,
	};
	
	FText DisplayName;
	FSimpleMulticastDelegate TaskStart;
	FSimpleMulticastDelegate TaskSucceed;
	FSimpleMulticastDelegate TaskFailed;
	ENamedThreads::Type EventThread;
	ENamedThreads::Type RunThread;
	TSharedRef<FRunnable> Runnable;
	std::atomic<ERunStatus> RunStatus;

	void OnRunnableExited(uint32 ExitCode);
public:
	virtual const FText& GetDisplayName() override { return DisplayName; }
	
	explicit FRunnableTaskRunner(const TSharedRef<FRunnable>& Runnable, const FText& DisplayName, ENamedThreads::Type RunThread);
	
	virtual bool Start(ENamedThreads::Type EventDispatchThread = ENamedThreads::AnyThread) override;
	virtual void Stop() override;

	virtual FSimpleMulticastDelegate& OnStart() override { return TaskStart; }
	virtual FSimpleMulticastDelegate& OnSucceed() override { return TaskSucceed; }
	virtual FSimpleMulticastDelegate& OnFailed() override { return TaskFailed; }
};