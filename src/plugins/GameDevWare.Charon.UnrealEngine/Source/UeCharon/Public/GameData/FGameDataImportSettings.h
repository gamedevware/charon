#pragma once

#include "FGameDataImportSettings.generated.h"

/*
 * Import-related information of UGameDataBase.
 */
USTRUCT()
struct FGameDataImportSettings
{
	GENERATED_BODY()

	/*
	 * Path to original file of imported game data. Should points to existing file within project folder. Relative to project's root.
	 */
	UPROPERTY(VisibleDefaultsOnly)
	FString OriginalAssetPath;

	/*
	 * MAD5 hash of imported OriginalAssetPath file.
	 */
	UPROPERTY(VisibleDefaultsOnly)
	FString OriginalAssetHash;
};

