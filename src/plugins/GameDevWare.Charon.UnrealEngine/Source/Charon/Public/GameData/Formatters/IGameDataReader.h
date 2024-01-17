#pragma once

#include "Containers/Array.h"
#include "Containers/Map.h"
#include "Containers/UnrealString.h"
#include "Templates/SharedPointer.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "Misc/Optional.h"
#include "Misc/DateTime.h"
#include "Misc/Timespan.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonTypes.h"
#include "Serialization/Archive.h"

/*
 * Base class for all implementation of game data readers.
 * Provides core de-serialization functionality over basic token reader implementation.
 */
class CHARON_API IGameDataReader
{
public:
	virtual ~IGameDataReader()
	{
	} // Virtual destructor

	// ReSharper disable CppFunctionIsNotImplemented
	virtual bool ReadNext() = 0;
	virtual const FString& GetIdentifier() const = 0;
	virtual const FString& GetValueAsString() const = 0;
	virtual double GetValueAsNumber() const = 0;
	virtual bool GetValueAsBoolean() const = 0;
	virtual const FString& GetErrorMessage() const = 0;
	virtual EJsonNotation GetNotation() = 0;
	virtual void SetErrorState(const FString& Message) = 0;
	// ReSharper enable CppFunctionIsNotImplemented

	bool ReadObject(TSharedPtr<FJsonObject>& JsonObject, const bool NextToken = true)
	{
		ReadObjectBegin();
		if (IsError())
		{
			return false;
		}
		while (GetNotation() != EJsonNotation::ObjectEnd)
		{
			auto MemberName = ReadMember();
			TSharedPtr<FJsonValue> MemberValue;
			if (!ReadAny(MemberValue) || IsError() || MemberValue == nullptr)
			{
				return false;
			}
			if (JsonObject == nullptr)
			{
				JsonObject = MakeShared<FJsonObject>();
			}
			JsonObject->SetField(MemberName, MemberValue);
		}
		ReadObjectEnd(NextToken);
		return true;
	}
	bool ReadArray(TArray<TSharedPtr<FJsonValue>>& JsonArray, const bool NextToken = true)
	{
		ReadArrayBegin();
		if (IsError())
		{
			return false;
		}
		while (GetNotation() != EJsonNotation::ArrayEnd)
		{
			TSharedPtr<FJsonValue> Item;
			if (!ReadAny(Item) || IsError() || Item == nullptr)
			{
				return false;
			}
			JsonArray.Add(Item);
		}
		ReadArrayEnd(NextToken);
		return true;
	}
	bool ReadAny(TSharedPtr<FJsonValue>& JsonValue, const bool NextToken = true)
	{
		switch (GetNotation())
		{
			case EJsonNotation::ArrayStart:
				{
					TArray<TSharedPtr<FJsonValue>> JsonArray;
					if (!ReadArray(JsonArray, false))
					{
						return false;
					}
					JsonValue = MakeShared<FJsonValueArray>(JsonArray);
					break;
				}
			case EJsonNotation::ObjectStart:
				{
					TSharedPtr<FJsonObject> JsonObject;
					if (!ReadObject(JsonObject, false))
					{
						return false;
					}
					JsonValue = MakeShared<FJsonValueObject>(JsonObject);
					break;
				}
			case EJsonNotation::Null:
				JsonValue = MakeShared<FJsonValueNull>();
				break;
			case EJsonNotation::String:
				JsonValue = MakeShared<FJsonValueString>(GetValueAsString());
				break;
			case EJsonNotation::Number:
				JsonValue = MakeShared<FJsonValueNumber>(GetValueAsNumber());
				break;
			case EJsonNotation::Boolean:
				JsonValue = MakeShared<FJsonValueBoolean>(GetValueAsBoolean());
				break;
			case EJsonNotation::Error:
				return false;
			default:
				SetErrorState("Unexpected notation.");
				return false;
		}

		if (NextToken)
		{
			ReadNext();
		}

		return true;
	}

	bool ReadArrayBegin(const bool NextToken = true)
	{
		if (IsError())
		{
			return false;
		}

		if (GetNotation() != EJsonNotation::ArrayStart)
		{
			SetErrorState("Unexpected token while ArrayStart is expected.");
			return false;
		}

		if (NextToken)
		{
			ReadNext();
		}

		return true;
	}
	bool ReadArrayEnd(const bool NextToken = true)
	{
		if (IsError())
		{
			return false;
		}

		if (GetNotation() != EJsonNotation::ArrayEnd)
		{
			SetErrorState("Unexpected token while ArrayEnd is expected.");
			return false;
		}
		if (NextToken)
		{
			ReadNext();
		}

		return true;
	}
	bool ReadObjectBegin(const bool NextToken = true)
	{
		if (IsError())
		{
			return false;
		}

		if (GetNotation() != EJsonNotation::ObjectStart)
		{
			SetErrorState("Unexpected token while ObjectStart is expected.");
			return false;
		}
		if (NextToken)
		{
			ReadNext();
		}

		return true;
	}
	bool ReadObjectEnd(const bool NextToken = true)
	{
		if (IsError())
		{
			return false;
		}

		if (GetNotation() != EJsonNotation::ObjectEnd)
		{
			SetErrorState("Unexpected token while ObjectEnd is expected.");
			return false;
		}
		if (NextToken)
		{
			ReadNext();
		}

		return true;
	}

	bool IsNull()
	{
		return GetNotation() == EJsonNotation::Null;
	}
	bool IsError()
	{
		return GetNotation() == EJsonNotation::Error;
	}

	const FString& ReadMember()
	{
		const FString& MemberName = GetIdentifier();

		// ReSharper disable once CppIncompleteSwitchStatement, CppDefaultCaseNotHandledInSwitchStatement
		switch (GetNotation())
		{
			case EJsonNotation::ArrayEnd: SetErrorState("Unexpected end of array when object's member is expected."); return MemberName;
			case EJsonNotation::ObjectEnd: SetErrorState("Unexpected end of object when object's member is expected."); return MemberName;
			case EJsonNotation::Error: return MemberName;
		}

		if (MemberName.IsEmpty())
		{
			SetErrorState("Unexpected empty member name. Probably array instead of object is read.");
			return MemberName;
		}
		return MemberName;
	}

	bool ReadValue(uint8& Value)
	{
		switch (GetNotation())
		{
			case EJsonNotation::String:
				Value = static_cast<uint8>(FCString::Atoi(*GetValueAsString()));
				return true;
			case EJsonNotation::Number:
				Value = static_cast<uint8>(GetValueAsNumber());
				return true;
			case EJsonNotation::Null:
				Value = 0;
				return true;
			default:
				return false;
		}
	}
	bool ReadValue(int32& Value)
	{
		switch (GetNotation())
		{
			case EJsonNotation::String:
				Value = FCString::Atoi(*GetValueAsString());
				return true;
			case EJsonNotation::Number:
				Value = static_cast<int32>(GetValueAsNumber());
				return true;
			case EJsonNotation::Null:
				Value = 0;
				return true;
			default:
				return false;
		}
	}
	bool ReadValue(int64& Value)
	{
		switch (GetNotation())
		{
			case EJsonNotation::String:
				Value = FCString::Atoi64(*GetValueAsString());
				return true;
			case EJsonNotation::Number:
				Value = static_cast<int64>(GetValueAsNumber());
				return true;
			case EJsonNotation::Null:
				Value = 0;
				return true;
			default:
				return false;
		}
	}
	bool ReadValue(float& Value)
	{
		switch (GetNotation())
		{
			case EJsonNotation::String:
				Value = FCString::Atof(*GetValueAsString());
				return true;
			case EJsonNotation::Number:
				Value = static_cast<float>(GetValueAsNumber());
				return true;
			case EJsonNotation::Null:
				Value = 0;
				return true;
			default:
				return false;
		}
	}
	bool ReadValue(double& Value)
	{
		switch (GetNotation())
		{
			case EJsonNotation::String:
				Value = FCString::Atod(*GetValueAsString());
				return true;
			case EJsonNotation::Number:
				Value = GetValueAsNumber();
				return true;
			case EJsonNotation::Null:
				Value = 0;
				return true;
			default:
				return false;
		}
	}
	bool ReadValue(bool& Value)
	{
		switch (GetNotation())
		{
			case EJsonNotation::String:
				Value = GetValueAsString().Equals("true", ESearchCase::IgnoreCase);
				return true;
			case EJsonNotation::Number:
				Value = GetValueAsNumber() > 0;
				return true;
			case EJsonNotation::Boolean:
				Value = GetValueAsBoolean();
				return true;
			case EJsonNotation::Null:
				Value = false;
				return true;
			default:
				return false;
		}
	}
	bool ReadValue(FString& Value)
	{
		switch (GetNotation())
		{
			case EJsonNotation::String:
				Value = GetValueAsString();
				return true;
			case EJsonNotation::Number:
				Value = FString::SanitizeFloat(GetValueAsNumber());
				return true;
			case EJsonNotation::Boolean:
				Value = GetValueAsBoolean() ? "True" : "False";
				return true;
			case EJsonNotation::Null:
				Value.Empty();
				return true;
			default:
				return false;
		}
	}
	bool ReadValue(FTimespan& Value)
	{
		switch (GetNotation())
		{
			case EJsonNotation::String:
				return FTimespan::Parse(GetValueAsString(), Value);
			case EJsonNotation::Number:
				Value = FTimespan(static_cast<int64>(GetValueAsNumber()));
				return true;
			case EJsonNotation::Null:
				Value = FTimespan(0);
				return true;
			default:
				return false;
		}
	}
	bool ReadValue(FDateTime& Value)
	{
		switch (GetNotation())
		{
			case EJsonNotation::String:
				return FDateTime::ParseIso8601(*GetValueAsString(), Value);
			case EJsonNotation::Null:
				Value = FDateTime();
				return true;
			default:
				return false;
		}
	}
	bool ReadValue(FVariant& Value)
	{
		switch (GetNotation())
		{
		case EJsonNotation::String:
			Value = FVariant(GetValueAsString());
			return true;
		case EJsonNotation::Number:
			Value = FVariant(GetValueAsNumber());
			return true;
		case EJsonNotation::Boolean:
			Value = FVariant(GetValueAsBoolean());
			return true;
		case EJsonNotation::Null:
			Value = FVariant();
			return true;
		default:
			return false;
		}
	}
	bool ReadValue(FText& Value)
	{
		switch (GetNotation())
		{
			case EJsonNotation::String:
				Value = FText::FromStringView(GetValueAsString());
				return true;
			case EJsonNotation::Number:
				Value = FText::FromStringView(FString::SanitizeFloat(GetValueAsNumber()));
				return true;
			case EJsonNotation::Boolean:
				Value = FText::FromString(GetValueAsBoolean() ? "True" : "False");
				return true;
			case EJsonNotation::Null:
				Value = FText::GetEmpty();
				return true;
			default:
				return false;
		}
	}

	template<typename T>
	bool ReadValue(TOptional<T>& Optional) {
		T Value;
		if (ReadValue(Value))
		{
			Optional = TOptional<T>(Value);
			return true;
		}
		return false;
	}

	template<typename EnumType, typename = std::enable_if_t<std::is_enum_v<EnumType>>>
	bool ReadValue(EnumType& EnumValue) {
		std::underlying_type_t<EnumType> Value;
		if (ReadValue(Value))
		{
			EnumValue = static_cast<EnumType>(Value);
			return true;
		}
		return false;
	}

	template<typename E>
	constexpr auto ReadEnumValue(TOptional<E>& OptionalEnumValue) -> bool {
		static_assert(std::is_enum_v<E>, "E must be an enum type");
		TOptional<std::underlying_type_t<E>> OptionalValue;
		if (ReadValue(OptionalValue) && OptionalValue.IsSet())
		{
			OptionalEnumValue = static_cast<E>(OptionalValue.GetValue());
			return true;
		}
		return false;
	}

	virtual void SkipAny(const bool NextToken = true)
	{
		if (GetNotation() == EJsonNotation::Error)
		{
			return;
		}

		uint32 ScopeCount = 0;
		EJsonNotation ClosingNotation = GetNotation();
		if (ClosingNotation == EJsonNotation::ArrayStart)
		{
			ClosingNotation = EJsonNotation::ArrayEnd;
		}
		else if (ClosingNotation == EJsonNotation::ObjectStart)
		{
			ClosingNotation = EJsonNotation::ObjectEnd;
		}
		else
		{
			ReadNext();
			return;
		}

		while (ReadNext())
		{
			if ((ScopeCount == 0) && (GetNotation() == ClosingNotation))
			{
				if (NextToken)
				{
					ReadNext();
				}
				return;
			}

			switch (GetNotation())
			{
			case EJsonNotation::ObjectStart:
			case EJsonNotation::ArrayStart:
				++ScopeCount;
				break;

			case EJsonNotation::ObjectEnd:
			case EJsonNotation::ArrayEnd:
				--ScopeCount;
				break;

			case EJsonNotation::Boolean:
			case EJsonNotation::Null:
			case EJsonNotation::Number:
			case EJsonNotation::String:
				break;

			case EJsonNotation::Error:
				return;
			}
		}
	}
};
