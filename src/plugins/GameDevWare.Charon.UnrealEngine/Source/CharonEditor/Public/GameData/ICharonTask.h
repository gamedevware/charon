#pragma once

class CHARONEDITOR_API ICharonTask
{
public:
	virtual ~ICharonTask() { }

	virtual const FText& GetDisplayName() = 0;
	
	virtual bool Start(ENamedThreads::Type EventDispatchThread = ENamedThreads::AnyThread) = 0;
	virtual void Stop() = 0;

	virtual FSimpleMulticastDelegate& OnStart() = 0;
	virtual FSimpleMulticastDelegate& OnSucceed() = 0;
	virtual FSimpleMulticastDelegate& OnFailed() = 0;

	static TSharedRef<ICharonTask> FromSimpleDelegate(const FSimpleDelegate& Delegate, const FText& DisplayName, ENamedThreads::Type RunThread = ENamedThreads::AnyThread);
	static TSharedRef<ICharonTask> FromRunnable(const TSharedRef<FRunnable>& Runnable, const FText& DisplayName, ENamedThreads::Type RunThread = ENamedThreads::AnyThread);
	static TSharedRef<ICharonTask> AsSequentialRunner(const TArray<TSharedRef<ICharonTask>>& Tasks);

protected:
	template<typename ThisType>
	static void BroadcastEvent(TWeakPtr<ThisType> WeakThisPtr, const FSimpleMulticastDelegate& CompletionFn, ENamedThreads::Type DispatchThread)
	{
		if (DispatchThread != ENamedThreads::AnyThread)
		{
			AsyncTask(DispatchThread, [WeakThisPtr, CompletionFn]
			{
				const auto ThisPtr = WeakThisPtr.Pin();
				if (!ThisPtr.IsValid()) { return; }
				CompletionFn.Broadcast();
			});
		}
		else
		{
			CompletionFn.Broadcast();
		}
	} 
};
