// Copyright Epic Games, Inc. All Rights Reserved.

#include "UeCharonEditor.h"

#include "GameData/FGameDataDocumentReference.h"
#include "FGameDataDocumentReferenceCustomization.h"
#include "PropertyEditorModule.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FUeCharonEditorModule"

void FUeCharonEditorModule::StartupModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomPropertyTypeLayout(
		FGameDataDocumentReference::StaticStruct()->GetFName(),
		FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FGameDataDocumentReferenceCustomization::MakeInstance));
	PropertyModule.NotifyCustomizationModuleChanged();
}

void FUeCharonEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.UnregisterCustomPropertyTypeLayout(FGameDataDocumentReference::StaticStruct()->GetFName());
		PropertyModule.NotifyCustomizationModuleChanged();
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUeCharonEditorModule, UeCharonEditor)