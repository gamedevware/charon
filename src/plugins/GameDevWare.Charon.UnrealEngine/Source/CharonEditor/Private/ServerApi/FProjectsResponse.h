#pragma once

#include "FProject.h"
#include "FApiError.h"

#include "FProjectsResponse.generated.h"

USTRUCT()
struct FProjectsResponse
{
	GENERATED_BODY();
	
	/** List of projects. */
	UPROPERTY(VisibleAnywhere)
	TArray<FProject> Result;

	/** Any error occurred during request. Null if no errors occurred. */
	UPROPERTY(VisibleAnywhere)
	TArray<FApiError> Errors;
};