#pragma once
#include "FGameDataEditorToolkit.h"

#include "UGameDataEditorWebBrowserBridge.generated.h"

UCLASS()
class UGameDataEditorWebBrowserBridge : public UObject
{
	GENERATED_BODY()
	
public:
	TWeakPtr<FGameDataEditorToolkit> EditorToolkit;
	
	UFUNCTION()
	bool Publish(FString Format, TArray<FString> Languages);
	
	UFUNCTION()
	bool GenerateSourceCode();
};

