#pragma once
#include "GameData\ICharonTask.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFDelegateTaskRunner, Log, All);

class FDelegateTaskRunner : public TSharedFromThis<FDelegateTaskRunner>, public ICharonTask
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
	ENamedThreads::Type DispatchThread;
	const FSimpleDelegate Delegate;
	std::atomic<ERunStatus> RunStatus;

	
public:
	virtual const FText& GetDisplayName() override { return DisplayName; }
	
	explicit FDelegateTaskRunner(const FSimpleDelegate& Delegate, const FText& DisplayName);

	virtual bool Run(ENamedThreads::Type EventDispatchThread = ENamedThreads::AnyThread) override;
	virtual void Stop() override;

	virtual FSimpleMulticastDelegate& OnStart() override { return TaskStart; }
	virtual FSimpleMulticastDelegate& OnSucceed() override { return TaskSucceed; }
	virtual FSimpleMulticastDelegate& OnFailed() override { return TaskFailed; }
};
