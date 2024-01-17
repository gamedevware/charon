#pragma once

#include "FDocumentValidationError.generated.h"

USTRUCT()
struct CHARONEDITOR_API FDocumentValidationError
{
	GENERATED_BODY();

	/** Path to faulted document/property. Format is JSON Pointer is https://datatracker.ietf.org/doc/html/rfc6901. */
	UPROPERTY(VisibleAnywhere, Category="Validation")
	FString Path;

	/** Message describing an error. */
	UPROPERTY(VisibleAnywhere, Category="Validation")
	FString Message;

	/** Unique code for error type. */
	UPROPERTY(VisibleAnywhere, Category="Validation")
	FString Code;
};