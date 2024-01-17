#pragma once
#include "EditorReimportHandler.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFGameDataReimportHandler, Log, All);

class FGameDataReimportHandler : public FReimportHandler
{
	//~ FReimportHandler interface
	virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames)  override;
	virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;
	virtual EReimportResult::Type Reimport(UObject* Obj) override;
	virtual int32 GetPriority() const override;
	//~ end of FReimportHandler
};
