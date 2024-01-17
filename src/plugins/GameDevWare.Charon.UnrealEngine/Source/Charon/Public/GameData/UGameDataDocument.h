
#pragma once

#include "CoreTypes.h"
#include "UObject/Class.h"
#include "UObject/ObjectPtr.h"
#include "Containers/Array.h"
#include "Containers/Map.h"
#include "Containers/UnrealString.h"
#include "Templates/SharedPointer.h"
#include "Internationalization/Text.h"
#include "Misc/Optional.h"
#include "Misc/DateTime.h"
#include "Misc/Timespan.h"

#include "UGameDataDocument.generated.h"

/*
 * Base class for all game data related documents. 
 */
UCLASS(BlueprintType, Abstract, NotBlueprintable)
class CHARON_API UGameDataDocument : public UObject
{
	GENERATED_BODY()
};

