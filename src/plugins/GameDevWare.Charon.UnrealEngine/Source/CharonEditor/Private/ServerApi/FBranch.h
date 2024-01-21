#pragma once

#include "FBranch.generated.h"

USTRUCT()
struct FBranch
{
	GENERATED_BODY();

	/** Id of branch, also it is dataSourceId. */
	UPROPERTY(VisibleAnywhere)
	FString Id;

	/** Name of branch. */
	UPROPERTY(VisibleAnywhere)
	FString Name;

	/** Is it primary branch. */
	UPROPERTY(VisibleAnywhere)
	bool IsPrimary;

	/** Size of branch. */
	UPROPERTY(VisibleAnywhere)
	int32 DataSize;
};