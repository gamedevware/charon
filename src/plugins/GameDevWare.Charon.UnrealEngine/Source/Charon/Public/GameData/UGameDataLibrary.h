#pragma once

#include "FGameDataDocumentReference.h"
#include "FLocalizedString.h"
#include "UGameDataDocument.h"

#include "UGameDataLibrary.generated.h"

UCLASS()
class UGameDataDocumentReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/*
	 * Get UGameDataDocument referenced in specified DocumentReference.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static UGameDataDocument* GetDocument(FGameDataDocumentReference DocumentReference)
	{
		return DocumentReference.GetReferencedDocument();
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
