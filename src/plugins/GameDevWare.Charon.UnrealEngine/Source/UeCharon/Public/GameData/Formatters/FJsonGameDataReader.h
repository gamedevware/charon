#pragma once
#include "IGameDataReader.h"

#include "Containers/UnrealString.h"
#include "Templates/SharedPointer.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonTypes.h"

/*
 * JSON format reader implementation with TJsonReader backed reader.
 */
class UECHARON_API FJsonGameDataReader final : public IGameDataReader
{
private:
	EJsonNotation Notation;
	FString ErrorMessage;
	TSharedRef<TJsonReader<UTF8CHAR>> JsonReader;

public:
	explicit FJsonGameDataReader(FArchive* const Stream);

	virtual bool ReadNext() override;
	virtual const FString& GetIdentifier() const override;
	virtual const FString& GetValueAsString() const override;
	virtual double GetValueAsNumber() const override;
	virtual bool GetValueAsBoolean() const override;
	virtual const FString& GetErrorMessage() const override;
	virtual EJsonNotation GetNotation() override;
	virtual void SetErrorState(const FString& Message) override;
};
