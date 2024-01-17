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

	const FText* FoundText;
	switch (LanguageSwitcher->FallbackOption)
	{
	case ELocalizedStringFallbackOption::OnNull:
	case ELocalizedStringFallbackOption::OnNotDefined:
		FoundText = TextByLanguageId.Find(LanguageSwitcher->CurrentLanguageId);
		if (FoundText != nullptr)
		{
			Current = *FoundText;
			break;
		}
		FoundText = TextByLanguageId.Find(LanguageSwitcher->FallbackLanguageId);
		if (FoundText != nullptr)
		{
			Current = *FoundText;
			break;
		}
		FoundText = TextByLanguageId.Find(LanguageSwitcher->PrimaryLanguageId);
		if (FoundText != nullptr)
		{
			Current = *FoundText;
			break;
		}
		Current = FText::GetEmpty();
		break;
	default:
	case ELocalizedStringFallbackOption::OnEmpty:
		CurrentValueLanguageId = CurrentLanguageId;
		FoundText = TextByLanguageId.Find(LanguageSwitcher->CurrentLanguageId);
		if (FoundText != nullptr && !FoundText->IsEmpty())
		{
			Current = *FoundText;
			break;
		}

		FoundText = TextByLanguageId.Find(LanguageSwitcher->FallbackLanguageId);
		if (FoundText != nullptr && !FoundText->IsEmpty())
		{
			Current = *FoundText;
			break;
		}

		FoundText = TextByLanguageId.Find(LanguageSwitcher->PrimaryLanguageId);
		if (FoundText != nullptr && !FoundText->IsEmpty())
		{
			Current = *FoundText;
			break;
		}

		Current = FText::GetEmpty();
		break;
	}

	return Current;
}
