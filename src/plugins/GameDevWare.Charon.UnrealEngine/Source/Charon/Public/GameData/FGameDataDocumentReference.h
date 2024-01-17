
#pragma once

#include "CoreTypes.h"
#include "Containers/Array.h"
#include "Containers/Map.h"
#include "Containers/UnrealString.h"
#include "Templates/SharedPointer.h"
#include "Internationalization/Text.h"
#include "UGameDataBase.h"

#include "FGameDataDocumentReference.generated.h"

class UGameDataDocument; // forward declaration

/*
 * Used to point into document within UGameDataBase. Could be used in Blueprints to reference document in imported UGameDataBase-derived asset.
 */
USTRUCT(BlueprintType)
struct CHARON_API FGameDataDocumentReference
{
	GENERATED_BODY()

public:
	/*
	 * Id of referenced document. Should be non-empty text to be valid.
	 */
	UPROPERTY(EditDefaultsOnly)
	FString Id;
	/*
	 * Schema Id or Name of referenced document. UClass name IS NOT valid for this purpose. Should be non-empty text to be valid.
	 */
	UPROPERTY(EditDefaultsOnly)
	FString SchemaIdOrName;
	/*
	 * Game data asset to look into.
	 */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UGameDataBase> GameData;

	/*
	 * True if all required field are properly filled. Not indicating existence of referenced document.
	 * Use GetReferencedDocument() to check existence of referenced document.
	 */
	bool IsValid() const
	{
		return !Id.IsEmpty() && !SchemaIdOrName.IsEmpty() && GameData != nullptr;
	}

	/*
	 * Get document referenced by this struct.
	 * Nullptr in case if document is not found.
	 * Use Cast<T> to get strongly typed version of document. 
	 */
	UGameDataDocument* GetReferencedDocument() const
	{
		if (!IsValid())
		{
			return nullptr;
		}
		return GameData->FindGameDataDocumentById(SchemaIdOrName, Id);
	}

	/*
	 * Get all documents referenced by References collection.
	 * In case if referenced documents are not found, nothing will be added to DocumentsById map. Partial resolve results apply.
	 */
	template <typename IdType, typename DocumentType>
	static void GetReferencedDocuments(TArray<FGameDataDocumentReference>& References, TMap<IdType, DocumentType*>& DocumentsById)
	{
		if (DocumentsById.Num() != 0 || References.Num() == 0)
		{
			return;
		}

		for (auto DocumentReference : References)
		{
			DocumentType* Document;
			GetReferencedDocument(DocumentReference, Document);
			if (Document != nullptr)
			{
				DocumentsById.Add(Document->Id, Document);
			}
		}

	}

	/*
	 * Get referenced document and put it into specified Document& output parameter.
	 */
	template <typename DocumentType>
	static void GetReferencedDocument(FGameDataDocumentReference& Reference, DocumentType*& Document)
	{
		if (Document != nullptr)
		{
			return;
		}

		const auto FoundDocument = Reference.GetReferencedDocument();
		if (FoundDocument == nullptr)
		{
			return;
		}

		if (FoundDocument->GetClass() != DocumentType::StaticClass())
		{
			return;
		}

		Document = Cast<DocumentType>(FoundDocument);
	}
};

