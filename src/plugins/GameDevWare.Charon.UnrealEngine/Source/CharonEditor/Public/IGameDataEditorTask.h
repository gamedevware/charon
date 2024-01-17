#pragma once

class CHARONEDITOR_API IGameDataEditorTask
{
public:
	virtual ~IGameDataEditorTask() { }

	virtual void Run(ENamedThreads::Type EventDispatchThread = ENamedThreads::AnyThread) = 0;
	virtual void Stop() const = 0;

	virtual FSimpleMulticastDelegate& OnSucceed() = 0;
	virtual FSimpleMulticastDelegate& OnFailed() = 0;
};
