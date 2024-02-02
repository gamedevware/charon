#pragma once

UENUM(BlueprintType)
/**
 * When to fallback to alternative localization text.
 */
enum class ELocalizedStringFallbackOption : uint8
{
	/**
	 * Fallback when the localized text is null (default)
	 */
	OnNull,
	/**
	 * Fallback when the localized text is an empty string
	 */
	OnEmpty,
	/**
	 * Fallback when the localized text is not defined in the LocalizedString
	 */
	OnNotDefined,
};

