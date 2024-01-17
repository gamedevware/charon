#pragma once

#include "CoreMinimal.h"
#include "EGameDataFormat.h"
#include "UGameDataDocument.h"
#include "UObject/Class.h"

#if WITH_EDITORONLY_DATA
#include "EditorFramework/AssetImportData.h"
#endif

#include "UGameDataBase.generated.h"

/*
 * Base class for specific game data classes. Provides methods and data for UE editor extensions and stores import-related information.
 */
UCLASS(BlueprintType, Abstract, NotBlueprintable)
class CHARON_API UGameDataBase : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/*
	 * Import-related information including original path to game data file.
	 */
	/**
	 * 
	 */
	UPROPERTY(VisibleAnywhere, Instanced, Category = ImportSettings)
	TObjectPtr<UAssetImportData> AssetImportData;

	/*
	 * Try to load game data from specified game data file/stream using specified file format.
	 * Used for import. Patch-enabled load method is defined on derived class. 
	 */
	virtual bool TryLoad(FArchive* const GameDataStream, EGameDataFormat Format) { return false; }

	/*
	 * Find UGameDataDocument of specified SchemaNameOrId by DocumentId. Returns nullptr if document or schema is not found. Used by FGameDataDocumentReference.
	 */
	virtual UGameDataDocument* FindGameDataDocumentById(const FString& SchemaNameOrId, const FString& DocumentId) { return  nullptr; }
	/*
	 * Find document UClass by specified SchemaNameOrId. Used by FGameDataDocumentReferenceCustomization.
	 */
	virtual UClass* FindDocumentSchemaClass(const FString& SchemaNameOrId) { return  nullptr; }
	/*
	 * Get all document ids by specified SchemaNameOrId. Used by FGameDataDocumentReferenceCustomization.
	 */
	virtual void GetDocumentIds(const FString& SchemaNameOrId, TArray<FString>& AllIds) { }
	/*
	 * Get all schema names defined in derived game data class. Used by FGameDataDocumentReferenceCustomization.
	 */
	virtual void GetDocumentSchemaNames(TArray<FString>& AllSchemaNames) { }

	virtual void PostInitProperties() override;
	virtual void PostLoad() override;
};