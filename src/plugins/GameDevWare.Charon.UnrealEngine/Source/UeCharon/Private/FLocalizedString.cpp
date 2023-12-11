
#include "GameData/FLocalizedString.h"

FLocalizedString::FLocalizedString
(
) : CurrentValueLanguageId()
 , Current(FText::GetEmpty())
 , LanguageSwitcher(nullptr)
 , TextByLanguageId()
{
}

FLocalizedString::FLocalizedString
(
	const FLocalizedString& Other
) : CurrentValueLanguageId(Other.CurrentValueLanguageId)
 , Current(Other.Current)
 , LanguageSwitcher(Other.LanguageSwitcher)
 , TextByLanguageId(Other.TextByLanguageId)
{
}

FLocalizedString::FLocalizedString
(
	const TMap<FString, FText>& TextByLanguageId,
	ULanguageSwitcher* LanguageSwitcher
) : CurrentValueLanguageId()
 , Current(FText::GetEmpty())
 , LanguageSwitcher(LanguageSwitcher)
 , TextByLanguageId(TextByLanguageId)
{
}

FText FLocalizedString::GetCurrent()
{
	if (LanguageSwitcher == nullptr)
	{
		return FText::GetEmpty();
	}

	const auto CurrentLanguageId = LanguageSwitcher->CurrentLanguageId;
	if (CurrentLanguageId == CurrentValueLanguageId)
	{
		return Current;
	}

	CurrentValueLanguageId = CurrentLanguageId;
	const FText* FoundText = TextByLanguageId.Find(CurrentLanguageId);
	if (FoundText != nullptr && !FoundText->IsEmpty())
	{
		return Current = *FoundText;
	}
	
	FoundText = TextByLanguageId.Find(LanguageSwitcher->FallbackLanguageId);
	if (FoundText != nullptr && !FoundText->IsEmpty())
	{
		return Current = *FoundText;
	}
	
	FoundText = TextByLanguageId.Find(LanguageSwitcher->PrimaryLanguageId);
	if (FoundText != nullptr && !FoundText->IsEmpty())
	{
		return Current = *FoundText;
	}
	
	return Current = FText::GetEmpty();
}


