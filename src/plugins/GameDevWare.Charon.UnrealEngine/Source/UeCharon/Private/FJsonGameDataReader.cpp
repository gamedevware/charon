#include "GameData/Formatters/FJsonGameDataReader.h"

FJsonGameDataReader::FJsonGameDataReader(FArchive* const Stream)
	: Notation(EJsonNotation::Null)
	  , ErrorMessage()
	  , JsonReader(TJsonReaderFactory<UTF8CHAR>::Create(Stream))
{
}

bool FJsonGameDataReader::ReadNext()
{
	if (Notation == EJsonNotation::Error)
	{
		return true;
	}

	const auto Result = JsonReader->ReadNext(Notation);
	if (Notation == EJsonNotation::Error)
	{
		ErrorMessage = JsonReader->GetErrorMessage();
	}
	return Result;
}

const FString& FJsonGameDataReader::GetIdentifier() const
{
	return JsonReader->GetIdentifier();
}

const FString& FJsonGameDataReader::GetValueAsString() const
{
	return JsonReader->GetValueAsString();
}

double FJsonGameDataReader::GetValueAsNumber() const
{
	return JsonReader->GetValueAsNumber();
}

bool FJsonGameDataReader::GetValueAsBoolean() const
{
	return JsonReader->GetValueAsBoolean();
}

const FString& FJsonGameDataReader::GetErrorMessage() const
{
	if (ErrorMessage.IsEmpty())
	{
		return JsonReader->GetErrorMessage();
	}
	else
	{
		return ErrorMessage;
	}
}

EJsonNotation FJsonGameDataReader::GetNotation()
{
	return Notation;
}

void FJsonGameDataReader::SetErrorState(const FString& Message)
{
	ErrorMessage = Message;
	Notation = EJsonNotation::Error;
}
