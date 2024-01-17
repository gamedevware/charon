#pragma once

/*
 * Collection of methods used to convert Document Ids to FString and back.
 */
class FGameDataDocumentIdConvert
{
public:
	static bool ConvertToType(const FString& ValueString, FString& Value) { Value = ValueString; return true; }
	static bool ConvertToType(const FString& ValueString, uint8& Value) { Value = static_cast<uint8>(FCString::Atoi(*ValueString)); return true; }
	static bool ConvertToType(const FString& ValueString, int32& Value) { Value = FCString::Atoi(*ValueString); return true; }
	static bool ConvertToType(const FString& ValueString, int64& Value) { Value = FCString::Atoi64(*ValueString); return true; }
	static bool ConvertToType(const FString& ValueString, float& Value) { Value = FCString::Atof(*ValueString); return true; }
	static bool ConvertToType(const FString& ValueString, double& Value) { Value = FCString::Atod(*ValueString); return true; }
	static bool ConvertToType(const FString& ValueString, bool& Value)  { Value = ValueString.Equals("true", ESearchCase::IgnoreCase); return true; }
	static bool ConvertToType(const FString& ValueString, FTimespan& Value) { return FTimespan::Parse(*ValueString, Value); }
	static bool ConvertToType(const FString& ValueString, FDateTime& Value) { return FDateTime::ParseIso8601(*ValueString, Value); }
	template<typename EnumType, typename = std::enable_if_t<std::is_enum_v<EnumType>>>
	static bool ConvertToType(const FString& ValueString, EnumType& Value) {
		std::underlying_type_t<EnumType> UnderlyingValue;

		static_assert(TIsEnum<EnumType>::Value, "Should only call this with enum types");
		const UEnum* EnumClass = StaticEnum<EnumType>();
		check(EnumClass != nullptr);
		const int64 FoundValue = EnumClass->GetValueByNameString(ValueString);
		if (FoundValue != INDEX_NONE)
		{
			Value = static_cast<EnumType>(FoundValue);
			return true;
		}
		
		if (ConvertToType(ValueString, UnderlyingValue))
		{
			Value = static_cast<EnumType>(UnderlyingValue);
			return true;
		}
		return false;
	}

	static bool ConvertToString(const FString& Value, FString& ValueString) { ValueString = Value; return true; }
	static bool ConvertToString(const uint8& Value, FString& ValueString) { ValueString = FString::Printf(TEXT("%d"), Value); return true; }
	static bool ConvertToString(const int32& Value, FString& ValueString) { ValueString = FString::Printf(TEXT("%d"), Value); return true; }
	static bool ConvertToString(const int64& Value, FString& ValueString) { ValueString = FString::Printf(TEXT("%lld"), Value); return true; }
	static bool ConvertToString(const float& Value, FString& ValueString) { ValueString = FString::SanitizeFloat(Value); return true; }
	static bool ConvertToString(const double& Value, FString& ValueString) { ValueString = FString::SanitizeFloat(Value); return true; }
	static bool ConvertToString(const bool& Value, FString& ValueString)  { ValueString = Value ? TEXT("True") : TEXT("False"); return true; }
	static bool ConvertToString(const FTimespan& Value, FString& ValueString) { ValueString = Value.ToString(); return true; }
	static bool ConvertToString(const FDateTime& Value, FString& ValueString) { ValueString = Value.ToIso8601(); return true; }
	template<typename EnumType, typename = std::enable_if_t<std::is_enum_v<EnumType>>>
	static bool ConvertToString(const EnumType& Value, FString& ValueString) {
		ValueString = UEnum::GetValueAsString(Value);
		const int SeparatorIndex = ValueString.Find(TEXT("::"));
		if (SeparatorIndex != INDEX_NONE)
		{
			ValueString.MidInline(SeparatorIndex + 2);	
		}
		return true;
	}
};
