#include "GameData/Formatters/FMessagePackGameDataReader.h"
#include "Misc/Base64.h"

enum EMessagePackType : uint8
{
	PositiveFixIntStart = 0x00,
	PositiveFixIntEnd = 0x7f,
	FixMapStart = 0x80,
	FixMapEnd = 0x8f,
	FixArrayStart = 0x90,
	FixArrayEnd = 0x9f,
	FixStrStart = 0xa0,
	FixStrEnd = 0xbf,
	Nil = 0xc0,
	Unused = 0xc1,
	False = 0xc2,
	True = 0xc3,
	Bin8 = 0xc4,
	Bin16 = 0xc5,
	Bin32 = 0xc6,
	Ext8 = 0xc7,
	Ext16 = 0xc8,
	Ext32 = 0xc9,
	Float32 = 0xca,
	Float64 = 0xcb,
	UInt8 = 0xcc,
	UInt16 = 0xcd,
	UInt32 = 0xce,
	UInt64 = 0xcf,
	Int8 = 0xd0,
	Int16 = 0xd1,
	Int32 = 0xd2,
	Int64 = 0xd3,
	FixExt1 = 0xd4,
	FixExt2 = 0xd5,
	FixExt4 = 0xd6,
	FixExt8 = 0xd7,
	FixExt16 = 0xd8,
	Str8 = 0xd9,
	Str16 = 0xda,
	Str32 = 0xdb,
	Array16 = 0xdc,
	Array32 = 0xdd,
	Map16 = 0xde,
	Map32 = 0xdf,
	NegativeFixIntStart = 0xe0,
	NegativeFixIntEnd = 0xff
};

enum EMessagePackParseMemberState : uint8
{
	EmptyStack = 0,
	NotAMap = 1,
	MemberNameExpected = 2,
	ValueExpected = 3,
	EndOfMapExpected = 4
};

void FMessagePackGameDataReader::DecrementClosingTokenCounter()
{
	if (ParseState.Num() <= 0)
	{
		return;
	}
	const auto TopToken = ParseState.Pop();
	PushClosingTokenCounter(TopToken.Key, TopToken.Value - 1);
}

void FMessagePackGameDataReader::PushClosingTokenCounter(EJsonNotation ClosingNotation, int32 Size)
{
	const auto NewState = TTuple<EJsonNotation, int32>(ClosingNotation, Size);
	ParseState.Push(NewState);
}

void FMessagePackGameDataReader::ReadBytes(TArray<uint8>& Buffer, const int32 NumBytes) const
{
	Buffer.SetNumUninitialized(NumBytes);
	for (int32 Index = 0; Index < NumBytes; ++Index)
	{
		(*Stream) << Buffer[Index];
	}
}

FMessagePackGameDataReader::FMessagePackGameDataReader(FArchive* const Stream)
	: Stream(Stream)
	  , ParseState()
	  , Notation(EJsonNotation::Null)
	  , CurrentToken(EJsonToken::None)
	  , Identifier()
	  , ErrorMessage()
	  , StringValue()
	  , NumberValue(0.0f)
	  , BoolValue(false)
	  , FinishedReadingRootObject(false)
{
}

bool FMessagePackGameDataReader::ReadNext()
{
	if (!ErrorMessage.IsEmpty())
	{
		Notation = EJsonNotation::Error;
		return false;
	}

	if (Stream == nullptr)
	{
		Notation = EJsonNotation::Error;
		SetErrorMessage(TEXT("Null Stream"));
		return true;
	}

	if (ParseState.Num() > 0 && ParseState.Top().Value == 0)
	{
		Notation = ParseState.Pop().Key;

		DecrementClosingTokenCounter();

		if (ParseState.Num() == 0)
		{
			FinishedReadingRootObject = true;
		}

		return true;
	}

	const bool AtEndOfStream = Stream->AtEnd();
	if (AtEndOfStream && FinishedReadingRootObject)
	{
		Notation = EJsonNotation::Error;
		SetErrorMessage(TEXT("Improperly formatted."));
		return true;
	}

	if (!AtEndOfStream && !FinishedReadingRootObject)
	{
		Notation = EJsonNotation::Error;
		SetErrorMessage(TEXT("Unexpected additional input found."));
		return true;
	}

	if (AtEndOfStream)
	{
		return false;
	}

	if (PeekParseMapState() != EMessagePackParseMemberState::ValueExpected)
	{
		Identifier.Empty();
	}

	uint8 FormatValue;
	Stream->Serialize(&FormatValue, 1);

	if (FormatValue >= EMessagePackType::FixArrayStart && FormatValue <= EMessagePackType::FixArrayEnd)
	{
		const auto ArraySize = FormatValue - EMessagePackType::FixArrayStart;
		PushClosingTokenCounter(EJsonNotation::ArrayEnd, ArraySize + 1);
		Notation = EJsonNotation::ArrayStart;
	}
	else if (FormatValue >= EMessagePackType::FixStrStart && FormatValue <= EMessagePackType::FixStrEnd)
	{
		const auto Utf8StringSize = FormatValue - EMessagePackType::FixStrStart;
		TArray<uint8> Utf8StringBytes;
		ReadBytes(Utf8StringBytes, Utf8StringSize);
		auto Utf8String = FString(UTF8_TO_TCHAR(Utf8StringBytes.GetData()));

		if (PeekParseMapState() == EMessagePackParseMemberState::MemberNameExpected)
		{
			DecrementClosingTokenCounter();

			Identifier = Utf8String;

			return ReadNext();
		}

		StringValue = Utf8String;
		Notation = EJsonNotation::String;
	}
	else if (FormatValue >= EMessagePackType::FixMapStart && FormatValue <= EMessagePackType::FixMapEnd)
	{
		const auto MapSize = FormatValue - EMessagePackType::FixMapStart;

		PushClosingTokenCounter(EJsonNotation::ObjectEnd, MapSize * 2 + 1);
		Notation = EJsonNotation::ObjectStart;
	}
	else if (FormatValue >= EMessagePackType::NegativeFixIntStart)
	{
		NumberValue = static_cast<int8>(FormatValue);
		Notation = EJsonNotation::Number;
	}
	else if (FormatValue <= EMessagePackType::PositiveFixIntEnd)
	{
		NumberValue = FormatValue;
		Notation = EJsonNotation::Number;
	}
	else
	{
		switch (FormatValue)
		{
		case EMessagePackType::Nil:
			Notation = EJsonNotation::Null;
			break;
		case EMessagePackType::Array16:
		case EMessagePackType::Array32:
			{
				uint32 ArraySize = 0;
				if (FormatValue == EMessagePackType::Array16)
				{
					uint16 SmallArraySize;
					Stream->Serialize(&SmallArraySize, 2);
					ArraySize = SmallArraySize;
				}
				else if (FormatValue == EMessagePackType::Array32)
				{
					Stream->Serialize(&ArraySize, 4);
				}

				PushClosingTokenCounter(EJsonNotation::ArrayEnd, ArraySize + 1);

				Notation = EJsonNotation::ArrayStart;
				break;
			}
		case EMessagePackType::Map16:
		case EMessagePackType::Map32:
			{
				uint32 MapSize = 0;
				if (FormatValue == EMessagePackType::Map16)
				{
					uint16 SmallMapSize;
					Stream->Serialize(&SmallMapSize, 2);
					MapSize = SmallMapSize;
				}
				else if (FormatValue == EMessagePackType::Map32)
				{
					Stream->Serialize(&MapSize, 4);
				}

				PushClosingTokenCounter(EJsonNotation::ObjectEnd, MapSize * 2 + 1);

				Notation = EJsonNotation::ObjectStart;
				break;
			}
		case EMessagePackType::Str16:
		case EMessagePackType::Str32:
		case EMessagePackType::Str8:
			{
				auto Utf8StringSize = 0L;
				if (FormatValue == EMessagePackType::Str8)
				{
					uint8 TinyStringSize = 0;
					Stream->Serialize(&TinyStringSize, 1);
					Utf8StringSize = TinyStringSize;
				}
				else if (FormatValue == EMessagePackType::Str16)
				{
					uint16 SmallStringSize = 0;
					Stream->Serialize(&SmallStringSize, 2);
					Utf8StringSize = SmallStringSize;
				}
				else if (FormatValue == EMessagePackType::Str32)
				{
					Stream->Serialize(&Utf8StringSize, 4);
				}

				if (Utf8StringSize > MAX_BINARY_LENGTH)
				{
					Notation = EJsonNotation::Error;
					SetErrorMessage(TEXT("Binary data is too long."));
					return true;
				}

				TArray<uint8> Utf8StringBytes;
				ReadBytes(Utf8StringBytes, Utf8StringSize);
				auto Utf8String = FString(UTF8_TO_TCHAR(Utf8StringBytes.GetData()));

				if (PeekParseMapState() == EMessagePackParseMemberState::MemberNameExpected)
				{
					DecrementClosingTokenCounter();

					Identifier = Utf8String;

					return ReadNext();
				}

				StringValue = Utf8String;
				Notation = EJsonNotation::String;
			}
		case EMessagePackType::Bin32:
		case EMessagePackType::Bin16:
		case EMessagePackType::Bin8:
			{
				auto BinarySize = 0L;
				if (FormatValue == EMessagePackType::Bin8)
				{
					uint8 TinyBinarySize = 0;
					Stream->Serialize(&TinyBinarySize, 1);
					BinarySize = TinyBinarySize;
				}
				else if (FormatValue == EMessagePackType::Bin16)
				{
					uint16 SmallBinarySize = 0;
					Stream->Serialize(&SmallBinarySize, 2);
					BinarySize = SmallBinarySize;
				}
				else if (FormatValue == EMessagePackType::Bin32)
				{
					Stream->Serialize(&BinarySize, 4);
				}

				if (BinarySize > MAX_BINARY_LENGTH)
				{
					Notation = EJsonNotation::Error;
					SetErrorMessage(TEXT("Binary data is too long."));
					return true;
				}

				TArray<uint8> BinaryBytes;
				ReadBytes(BinaryBytes, BinarySize);
				auto BinaryBase64 = FBase64::Encode(BinaryBytes);

				StringValue = BinaryBase64;
				Notation = EJsonNotation::String;
				break;
			}
		case EMessagePackType::FixExt1:
		case EMessagePackType::FixExt16:
		case EMessagePackType::FixExt2:
		case EMessagePackType::FixExt4:
		case EMessagePackType::FixExt8:
		case EMessagePackType::Ext32:
		case EMessagePackType::Ext16:
		case EMessagePackType::Ext8:
			{
				uint32 ExtSize = 0;
				if (FormatValue == EMessagePackType::FixExt1)
				{
					ExtSize = 1;
				}
				else if (FormatValue == EMessagePackType::FixExt2)
				{
					ExtSize = 2;
				}
				else if (FormatValue == EMessagePackType::FixExt4)
				{
					ExtSize = 4;
				}
				else if (FormatValue == EMessagePackType::FixExt8)
				{
					ExtSize = 8;
				}
				else if (FormatValue == EMessagePackType::FixExt16)
				{
					ExtSize = 16;
				}
				if (FormatValue == EMessagePackType::Ext8)
				{
					uint8 TinyExtSize;
					Stream->Serialize(&TinyExtSize, 1);
					ExtSize = TinyExtSize;
				}
				else if (FormatValue == EMessagePackType::Ext16)
				{
					uint16 SmallExtSize;
					Stream->Serialize(&SmallExtSize, 2);
					ExtSize = SmallExtSize;
				}
				else if (FormatValue == EMessagePackType::Ext32)
				{
					Stream->Serialize(&ExtSize, 4);
				}

				if (ExtSize > MAX_BINARY_LENGTH)
				{
					Notation = EJsonNotation::Error;
					SetErrorMessage(TEXT("Extension data is too long."));
					return true;
				}

				TArray<uint8> ExtBytes;
				ReadBytes(ExtBytes, ExtSize);
				auto ExtBase64 = FBase64::Encode(ExtBytes);

				StringValue = ExtBase64;
				Notation = EJsonNotation::String;
				break;
			}
		case EMessagePackType::False:
			BoolValue = false;
			Notation = EJsonNotation::Boolean;
			break;
		case EMessagePackType::True:
			BoolValue = true;
			Notation = EJsonNotation::Boolean;
			break;
		case EMessagePackType::Float32:
			{
				float Float32Value;
				Stream->Serialize(&Float32Value, 4);
				NumberValue = Float32Value;
				Notation = EJsonNotation::Number;
				break;
			}
		case EMessagePackType::Float64:
			Stream->Serialize(&NumberValue, 8);
			Notation = EJsonNotation::Number;
			break;
		case EMessagePackType::Int8:
			{
				int8 Int8Value;
				Stream->Serialize(&Int8Value, 1);
				NumberValue = Int8Value;
				Notation = EJsonNotation::Number;
				break;
			}
		case EMessagePackType::Int16:
			{
				int16 Int16Value;
				Stream->Serialize(&Int16Value, 2);
				NumberValue = Int16Value;
				Notation = EJsonNotation::Number;
				break;
			}
		case EMessagePackType::Int32:
			{
				int32 Int32Value;
				Stream->Serialize(&Int32Value, 4);
				NumberValue = Int32Value;
				Notation = EJsonNotation::Number;
				break;
			}
		case EMessagePackType::Int64:
			{
				int64 Int64Value;
				Stream->Serialize(&Int64Value, 8);
				if (Int64Value >= INT32_MAX || Int64Value <= INT32_MIN)
				{
					StringValue = FString::Printf(TEXT("%lld"), Int64Value);
					Notation = EJsonNotation::String;
				}
				else
				{
					NumberValue = Int64Value;
					Notation = EJsonNotation::Number;
				}
				break;
			}
		case EMessagePackType::UInt8:
			{
				uint8 UInt8Value;
				Stream->Serialize(&UInt8Value, 1);
				NumberValue = UInt8Value;
				Notation = EJsonNotation::Number;
				break;
			}
		case EMessagePackType::UInt16:
			{
				uint16 UInt16Value;
				Stream->Serialize(&UInt16Value, 2);
				NumberValue = UInt16Value;
				Notation = EJsonNotation::Number;
				break;
			}
		case EMessagePackType::UInt32:
			{
				uint32 UInt32Value;
				Stream->Serialize(&UInt32Value, 4);
				NumberValue = UInt32Value;
				Notation = EJsonNotation::Number;
				break;
			}
		case EMessagePackType::UInt64:
			{
				uint64 UInt64Value;
				Stream->Serialize(&UInt64Value, 8);
				if (UInt64Value >= INT32_MAX)
				{
					StringValue = FString::Printf(TEXT("%lld"), UInt64Value);
					Notation = EJsonNotation::String;
				}
				else
				{
					NumberValue = UInt64Value;
					Notation = EJsonNotation::Number;
				}
				break;
			}
		case EMessagePackType::PositiveFixIntStart:
		case EMessagePackType::PositiveFixIntEnd:
		case EMessagePackType::FixMapStart:
		case EMessagePackType::FixMapEnd:
		case EMessagePackType::FixArrayStart:
		case EMessagePackType::FixArrayEnd:
		case EMessagePackType::FixStrStart:
		case EMessagePackType::FixStrEnd:
		case EMessagePackType::Unused:
		case EMessagePackType::NegativeFixIntStart:
		case EMessagePackType::NegativeFixIntEnd:
		default:
			Notation = EJsonNotation::Error;
			SetErrorMessage(TEXT("Unexpected Message Pack notation."));
			return true;
		}
	}

	DecrementClosingTokenCounter();

	return true;
}

const FString& FMessagePackGameDataReader::GetIdentifier() const
{
	return Identifier;
}

const FString& FMessagePackGameDataReader::GetValueAsString() const
{
	check(CurrentToken == EJsonToken::String);

	return StringValue;
}

double FMessagePackGameDataReader::GetValueAsNumber() const
{
	check(CurrentToken == EJsonToken::Number);

	return NumberValue;
}

bool FMessagePackGameDataReader::GetValueAsBoolean() const
{
	check((CurrentToken == EJsonToken::True) || (CurrentToken == EJsonToken::False));

	return BoolValue;
}

const FString& FMessagePackGameDataReader::GetErrorMessage() const
{
	return ErrorMessage;
}

EJsonNotation FMessagePackGameDataReader::GetNotation()
{
	return Notation;
}

void FMessagePackGameDataReader::SetErrorState(const FString& Message)
{
	ErrorMessage = Message;
	Notation = EJsonNotation::Error;
}

void FMessagePackGameDataReader::SetErrorMessage(const FString& Message)
{
	ErrorMessage = Message;
}

uint8 FMessagePackGameDataReader::PeekParseMapState()
{
	if (ParseState.Num() == 0)
	{
		return EMessagePackParseMemberState::EmptyStack;
	}
	const auto ClosingToken = ParseState.Top();
	if (ClosingToken.Key != EJsonNotation::ObjectEnd)
	{
		return EMessagePackParseMemberState::NotAMap;
	}
	else if (ClosingToken.Value == 0)
	{
		return EMessagePackParseMemberState::EndOfMapExpected;
	}
	else if ((ClosingToken.Value % 2) == 0)
	{
		return EMessagePackParseMemberState::MemberNameExpected;
	}
	else
	{
		return EMessagePackParseMemberState::ValueExpected;
	}
}
