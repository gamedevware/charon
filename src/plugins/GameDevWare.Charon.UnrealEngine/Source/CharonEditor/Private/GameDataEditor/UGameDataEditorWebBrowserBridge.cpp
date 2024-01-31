#include "UGameDataEditorWebBrowserBridge.h"

// ReSharper disable CppMemberFunctionMayBeConst, CppParameterNeverUsed

bool UGameDataEditorWebBrowserBridge::Publish(FString Format, TArray<FString> Languages)
{
	const auto EditorToolkitPtr = EditorToolkit.Pin();
	if (!EditorToolkitPtr.IsValid()) { return false; } 
	EditorToolkitPtr->Sync_Execute();
	return true;
}

bool UGameDataEditorWebBrowserBridge::GenerateSourceCode()
{
	const auto EditorToolkitPtr = EditorToolkit.Pin();
	if (!EditorToolkitPtr.IsValid()) { return false; } 
	EditorToolkitPtr->GenerateSourceCode_Execute();
	return true;
}
