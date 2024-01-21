#pragma once

#include "FDocumentValidationError.h"

#include "FDocumentValidationRecord.generated.h"

USTRUCT()
struct CHARONEDITOR_API FDocumentValidationRecord
{
	GENERATED_BODY();

	/** Id of the changed document. */
	UPROPERTY(VisibleAnywhere, Category="Validation")
	FString Id;

	/** Schema name of changed document. */
	UPROPERTY(VisibleAnywhere, Category="Change")
	FString SchemaName;
	
	/** Schema name of changed document. */
	UPROPERTY(VisibleAnywhere, Category="Change")
	FString SchemaId;

	/** List of document's errors. */
	UPROPERTY(VisibleAnywhere, Category="Change")
	TArray<FDocumentValidationError> Errors;
};