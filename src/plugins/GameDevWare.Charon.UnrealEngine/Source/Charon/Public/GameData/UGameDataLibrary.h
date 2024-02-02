#pragma once

#include "FGameDataDocumentReference.h"
#include "EDocumentReferenceGetResult.h"
#include "FLocalizedString.h"
#include "UGameDataDocument.h"

#include "UGameDataLibrary.generated.h"

/*
 * Additional function for Blueprints related to game data.
 */
UCLASS()
class UGameDataDocumentReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/*
	 * Get UGameDataDocument referenced in specified DocumentReference.
	 */
	UFUNCTION(BlueprintCallable, Meta = (ExpandEnumAsExecs = "Branches"))
	static UGameDataDocument* GetDocument(FGameDataDocumentReference DocumentReference, EDocumentReferenceGetResult& Branches)
	{
		UGameDataDocument* Document = DocumentReference.GetReferencedDocument();
		if (Document == nullptr)
		{
			Branches = EDocumentReferenceGetResult::NotFound;
		}
		else
		{
			Branches = EDocumentReferenceGetResult::Found;
		}
		return Document;
	}

	/*
	 * Get current text specified in internal ULanguageSwitcher of selected LocalizedString.
	 */
	UFUNCTION(BlueprintCallable)
	static FText GetCurrentText(FLocalizedString LocalizedString)
	{
		return LocalizedString.GetCurrent();
	}
};
