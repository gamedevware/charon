#pragma once

#include "CoreMinimal.h"
#include "EditorReimportHandler.h"
#include "Factories/Factory.h"
#include "Factories/ImportSettings.h"
#include "UObject/ObjectMacros.h"
#include "UObject/UObjectGlobals.h"
#include "Engine/Texture.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Misc/FeedbackContext.h"
#include "Templates/SubclassOf.h"

#include "GameData/UGameDataBase.h"

#include "UGameDataFactory.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogUGameDataFactory, Log, All);

/*
 * Importing/re-importing provider for UGameDataBase derived classes.
 */
UCLASS(CustomConstructor, CollapseCategories, ShowCategories=Object)
class CHARONEDITOR_API UGameDataFactory: public UFactory, public IImportSettingsParser
{
	GENERATED_BODY()

private:
	/** Texture settings from the automated importer that should be applied to the new texture */
	TSharedPtr<class FJsonObject> AutomatedImportSettings;

public:
	UPROPERTY(EditAnywhere, Category=DataAsset)
	TSubclassOf<UGameDataBase> GameDataClass;
	
	UGameDataFactory(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~ Begin UFactory Interface
	virtual bool ConfigureProperties() override;
	virtual void CleanUp() override;
	virtual bool DoesSupportClass(UClass* Class) override;
	virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;
	virtual UObject* FactoryCreateBinary( UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn ) override;
	virtual bool FactoryCanImport(const FString& Filename) override;
	virtual IImportSettingsParser* GetImportSettingsParser() override;

	//~ End UFactory Interface

	/** IImportSettingsParser interface */
	virtual void ParseFromJson(TSharedRef<FJsonObject> ImportSettingsJson) override;
};
