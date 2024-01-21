#pragma once

#include "FApiError.generated.h"

USTRUCT()
struct FApiError
{
	GENERATED_BODY();
	
	/** Error message. */
	UPROPERTY(VisibleAnywhere)
	FString Message;

	/** Error code. */
	UPROPERTY(VisibleAnywhere)
	FString Code;
};