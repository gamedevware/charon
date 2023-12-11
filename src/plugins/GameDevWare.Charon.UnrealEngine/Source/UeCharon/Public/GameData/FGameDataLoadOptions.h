
#pragma once

#include "EGameDataFormat.h"
#include "CoreMinimal.h"
#include "Containers/Array.h"
#include "Templates/SharedPointer.h"

/*
 * Various option of loading game data from stream. 
 */
struct FGameDataLoadOptions
{
	FGameDataLoadOptions() : Format(EGameDataFormat::Json)
	{  }

public:
	/*
	 * Format of passed game data file/stream. Also defines format of Patches collection. So all patches should be in same format as primary game data stream.
	 */
	EGameDataFormat Format;
	/*
	 * Optional list of patches to apply on game data in same format as primary stream. Values SHOULD NOT be nullptr. 
	 */
	TArray<FArchive*> Patches;
};

