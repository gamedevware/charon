#include "GameData/Formatters/FJsonObjectGameDataReader.h"

FJsonObjectGameDataReader::FJsonObjectReaderFrame::FJsonObjectReaderFrame(TSharedPtr<FJsonObject>& JsonObject)
{
	CurrentIndex = 0;
	MemberNameIsVisited = false;
	CurrentObject = &JsonObject;
	CurrentObject->Get()->Values.GetKeys(CurrentObjectKeys);
	CurrentArray = nullptr;
}

FJsonObjectGameDataReader::FJsonObjectReaderFrame::FJsonObjectReaderFrame(TArray<TSharedPtr<FJsonValue>>& JsonObject)
{
	CurrentIndex = 0;
	MemberNameIsVisited = false;
	CurrentObject = nullptr;
	CurrentObjectKeys = TArray<FString>();
	CurrentArray = &JsonObject;
}

FString& FJsonObjectGameDataReader::FJsonObjectReaderFrame::GetCurrentMemberName()
{
	return CurrentObjectKeys[CurrentIndex];
}

TSharedPtr<FJsonValue> FJsonObjectGameDataReader::FJsonObjectReaderFrame::GetCurrentValue()
{
	if (CurrentArray != nullptr)
	{
		return (*CurrentArray)[CurrentIndex];
	}
	else
	{
		const auto MemberName = CurrentObjectKeys[CurrentIndex];
		return CurrentObject->Get()->GetField<EJson::None>(MemberName);
	}
}

EJson FJsonObjectGameDataReader::FJsonObjectReaderFrame::GetContainerToken() const
{
	if (CurrentArray != nullptr)
	{
		return EJson::Array;
	}
	else
	{
		return EJson::Object;
	}
}

void FJsonObjectGameDataReader::FJsonObjectReaderFrame::NextMemberOrItem()
{
	this->CurrentIndex++;
	this->MemberNameIsVisited = false;
}

EJsonToken FJsonObjectGameDataReader::FJsonObjectReaderFrame::GetNextJsonToken()
{
	const bool bIsObject = CurrentArray == nullptr;
	if (CurrentIndex >= (bIsObject ? CurrentObjectKeys.Num() : CurrentArray->Num()))
	{
		return bIsObject ? EJsonToken::CurlyClose : EJsonToken::SquareClose;
	}

	if (bIsObject && !MemberNameIsVisited)
	{
		MemberNameIsVisited = true;
		return EJsonToken::Identifier;
	}

	MemberNameIsVisited = false;

	const auto CurrentValue = GetCurrentValue();
	switch (CurrentValue->Type)
	{
	case EJson::Array: return EJsonToken::SquareOpen;
	case EJson::Object: return EJsonToken::CurlyOpen;
	case EJson::Null: return EJsonToken::Null;
	case EJson::Number: return EJsonToken::Number;
	case EJson::Boolean:
		bool bIsTrue;
		CurrentValue->TryGetBool(bIsTrue);
		return bIsTrue ? EJsonToken::True : EJsonToken::False;
	case EJson::String: return EJsonToken::String;
	case EJson::None:
	default: return EJsonToken::None;
	}
}

FJsonObjectGameDataReader::FJsonObjectGameDataReader(const TSharedPtr<FJsonObject>& JsonObject)
	: Notation(EJsonNotation::Null)
	  , CurrentToken(EJsonToken::None)
	  , Identifier()
	  , ErrorMessage()
	  , StringValue()
	  , NumberValue(0.0f)
	  , BoolValue(false)
	  , FinishedReadingRootObject(false)
{
	this->Frames = TArray<FJsonObjectReaderFrame>();
	this->JsonObject = JsonObject;
	this->CurrentToken = EJsonToken::None;
}

bool FJsonObjectGameDataReader::ReadNext()
{
	if (Frames.Num() == 0 && !FinishedReadingRootObject)
	{
		Notation = EJsonNotation::ObjectStart;
		this->Frames.Push(FJsonObjectReaderFrame(JsonObject));

		return true;
	}

	while (Frames.Num() >= 0)
	{
		FJsonObjectReaderFrame& TopFrame = Frames.Top();
		switch (TopFrame.GetNextJsonToken())
		{
		case EJsonToken::CurlyOpen:
			{
				TSharedPtr<FJsonObject>* CurrentJsonObject;
				const bool bGetObjectSuccess = TopFrame.GetCurrentValue().Get()->TryGetObject(CurrentJsonObject);
				ensure(bGetObjectSuccess);
				ensure(CurrentJsonObject != nullptr);
				TopFrame.NextMemberOrItem();
				Frames.Push(FJsonObjectReaderFrame(*CurrentJsonObject));
				Notation = EJsonNotation::ObjectStart;
				return true;
			}
		case EJsonToken::CurlyClose:
			Notation = EJsonNotation::ObjectEnd;
			Frames.Pop();
			if (Frames.Num() == 0)
			{
				FinishedReadingRootObject = true;
			}
			return true;
		case EJsonToken::SquareOpen:
			{
				TArray<TSharedPtr<FJsonValue>>* CurrentJsonArray;
				const bool bGetArraySuccess = TopFrame.GetCurrentValue().Get()->TryGetArray(CurrentJsonArray);
				ensure(bGetArraySuccess);
				ensure(CurrentJsonArray != nullptr);
				TopFrame.NextMemberOrItem();
				Frames.Push(FJsonObjectReaderFrame(*CurrentJsonArray));
				Notation = EJsonNotation::ArrayStart;
				return true;
			}
		case EJsonToken::SquareClose:
			Frames.Pop();
			Notation = EJsonNotation::ArrayEnd;
			return true;
		case EJsonToken::String:
			Notation = EJsonNotation::String;
			TopFrame.GetCurrentValue().Get()->TryGetString(this->StringValue);
			TopFrame.NextMemberOrItem();
			return true;
		case EJsonToken::Number:
			Notation = EJsonNotation::Number;
			TopFrame.GetCurrentValue().Get()->TryGetNumber(this->NumberValue);
			TopFrame.NextMemberOrItem();
			return true;
		case EJsonToken::False:
		case EJsonToken::True:
			Notation = EJsonNotation::Boolean;
			TopFrame.GetCurrentValue().Get()->TryGetBool(this->BoolValue);
			TopFrame.NextMemberOrItem();
			return true;
		case EJsonToken::Null:
			Notation = EJsonNotation::Null;
			TopFrame.NextMemberOrItem();
			return true;
		case EJsonToken::Identifier:
			this->Identifier = TopFrame.GetCurrentMemberName();
			continue;
		case EJsonToken::None:
			break;
		case EJsonToken::Comma:
		case EJsonToken::Colon:
		default:
			continue;
		}
	}

	return false;
}

const FString& FJsonObjectGameDataReader::GetIdentifier() const
{
	return Identifier;
}

const FString& FJsonObjectGameDataReader::GetValueAsString() const
{
	check(CurrentToken == EJsonToken::String);

	return StringValue;
}

double FJsonObjectGameDataReader::GetValueAsNumber() const
{
	check(CurrentToken == EJsonToken::Number);

	return NumberValue;
}

bool FJsonObjectGameDataReader::GetValueAsBoolean() const
{
	check((CurrentToken == EJsonToken::True) || (CurrentToken == EJsonToken::False));

	return BoolValue;
}

const FString& FJsonObjectGameDataReader::GetErrorMessage() const
{
	return ErrorMessage;
}

EJsonNotation FJsonObjectGameDataReader::GetNotation()
{
	return Notation;
}

void FJsonObjectGameDataReader::SetErrorState(const FString& Message)
{
	ErrorMessage = Message;
	Notation = EJsonNotation::Error;
}
