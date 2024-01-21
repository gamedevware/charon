#pragma once

#include "FProject.generated.h"

USTRUCT()
struct FProject
{
	GENERATED_BODY();

	/** Id of project. */
	UPROPERTY(VisibleAnywhere)
	FString Id;

	/** Name of project. */
	UPROPERTY(VisibleAnywhere)
	FString Name;

	/** Picture URL of project. */
	UPROPERTY(VisibleAnywhere)
	FString PictureUrl;

	/** Picture URL of project. */
	UPROPERTY(VisibleAnywhere)
	TArray<FBranch> Branches;
};