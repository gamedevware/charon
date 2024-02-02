#pragma once

/**
 * @class ICharonTask
 * @brief Represents a startable task with status events and a display name. This is the basis for all long running operations within the plugin.
 *
 * This interface defines the essential functionalities for tasks within the Charon Editor plugin, 
 * including starting and stopping tasks, accessing task display names, and handling task events.
 */
class CHARONEDITOR_API ICharonTask
{
public:
	/**
	 * Virtual destructor for interface.
	 */
	virtual ~ICharonTask()
	{
	}

	/**
	   * Retrieves the display name of the task, primarily used for logging purposes.
	   *
	   * @return The display name of the task as FText.
	   */
	virtual const FText& GetDisplayName() = 0;

	/**
	  * Starts the task, with the option to specify the thread for dispatching OnStart(), OnSucceed(), and OnFailed() events.
	  * If it returns false, then no events will be fired due to initial misconfiguration of the task, or if the task is already running or finished.
	  * This method should be called only once.
	  *
	  * @param EventDispatchThread The thread on which the events should be dispatched. Defaults to ENamedThreads::AnyThread.
	  * @return true if the task was started successfully, false otherwise.
	  */
	virtual bool Start(ENamedThreads::Type EventDispatchThread = ENamedThreads::AnyThread) = 0;
	/**
	 * Attempts to stop a running task. This method has no effect on a task that has finished or has not been started.
	 * It is safe to call this method multiple times or from multiple threads.
	 */
	virtual void Stop() = 0;

	/**
	 * Event that fires when the task is started.
	 *
	 * @return A reference to the FSimpleMulticastDelegate that can be used to bind event handlers for task start.
	 */
	virtual FSimpleMulticastDelegate& OnStart() = 0;
	/**
	 * Event that fires when the task succeeds.
	 *
	 * @return A reference to the FSimpleMulticastDelegate that can be used to bind event handlers for task success.
	 */
	virtual FSimpleMulticastDelegate& OnSucceed() = 0;
	/**
	 * Event that fires when the task fails.
	 *
	 * @return A reference to the FSimpleMulticastDelegate that can be used to bind event handlers for task failure.
	 */
	virtual FSimpleMulticastDelegate& OnFailed() = 0;

	/**
	 * Creates an instance of a task from a simple delegate.
	 *
	 * @param Delegate The delegate to be executed by the task.
	 * @param DisplayName The display name of the task for logging purposes.
	 * @param RunThread The thread on which the delegate should be run. Defaults to ENamedThreads::AnyThread.
	 * @return A shared reference to the newly created ICharonTask instance.
	 */
	static TSharedRef<ICharonTask> FromSimpleDelegate(const FSimpleDelegate& Delegate, const FText& DisplayName, ENamedThreads::Type RunThread = ENamedThreads::AnyThread);
	/**
	 * Creates an instance of a task from an Unreal Engine FRunnable implementation.
	 * The runnable should be a non-started instance or an instance that allows multiple runs.
	 *
	 * @param Runnable The FRunnable to be executed by the task.
	 * @param DisplayName The display name of the task for logging purposes.
	 * @param RunThread The thread on which the runnable should be run. Defaults to ENamedThreads::AnyThread.
	 * @return A shared reference to the newly created ICharonTask instance.
	 */
	static TSharedRef<ICharonTask> FromRunnable(const TSharedRef<FRunnable>& Runnable, const FText& DisplayName, ENamedThreads::Type RunThread = ENamedThreads::AnyThread);
	/**
	 * Combines multiple tasks into a single task and runs them sequentially.
	 * The combined task only fails if Stop() is called on it; failures from inner tasks do not propagate to the combined task.
	 *
	 * @param Tasks An array of tasks to be run sequentially.
	 * @return A shared reference to the newly created ICharonTask instance that represents the sequential runner.
	 */
	static TSharedRef<ICharonTask> AsSequentialRunner(const TArray<TSharedRef<ICharonTask>>& Tasks);

protected:
	template <typename ThisType>
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
