
#pragma once

#include "CoreTypes.h"
#include "Containers/Array.h"
#include "Containers/Map.h"
#include "Containers/UnrealString.h"
#include "Templates/SharedPointer.h"
#include "Internationalization/Text.h"
#include "ULanguageSwitcher.h"

#include "FLocalizedString.generated.h"

/*
 * Collection of translated text by BCP-47 language tag.
 * Internally it is just Map of FText by language tag.
 * To change value returned by GetCurrent() use SetLanguage() method on your UGameDataBase-derived class.
 */
USTRUCT(BlueprintType)
struct UECHARON_API FLocalizedString
{
	GENERATED_BODY()

private:
	FString CurrentValueLanguageId;
	FText Current;
	
	UPROPERTY()
	ULanguageSwitcher* LanguageSwitcher;
	
public:
	FLocalizedString();
	FLocalizedString(const FLocalizedString& Other);
	FLocalizedString(const TMap<FString, FText>& TextByLanguageId,
					 ULanguageSwitcher* LanguageSwitcher);

	/*
	 * Map of FText by BCP-47 language tag. Values could be empty FTexts. Not all supported language tags could present in map.
	 */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FString, FText> TextByLanguageId;

	/*
	 * Get FText of currently selected language. Use SetLanguage() method on your UGameDataBase-derived class to change current FText for whole game data.
	 */
	FText GetCurrent();
};

