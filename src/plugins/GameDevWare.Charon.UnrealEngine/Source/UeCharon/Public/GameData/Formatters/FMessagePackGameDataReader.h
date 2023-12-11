#pragma once
#include "IGameDataReader.h"

#include "Containers/Array.h"
#include "Containers/UnrealString.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "Templates/SharedPointer.h"
#include "Templates/Tuple.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonTypes.h"
#include "Serialization/Archive.h"

/*
 * MessagePack format reader implementation with TJsonReader backed token types.
 */
class UECHARON_API FMessagePackGameDataReader final : public IGameDataReader
{
private:
	FArchive* Stream;
	TArray<TTuple<EJsonNotation, int32>> ParseState;
	EJsonNotation Notation;
	EJsonToken CurrentToken;
	FString Identifier;
	FString ErrorMessage;
	FString StringValue;
	double NumberValue;
	bool BoolValue;
	bool FinishedReadingRootObject;

	void PushClosingTokenCounter(EJsonNotation ClosingNotation, int32 Size);
	void DecrementClosingTokenCounter();
	void ReadBytes(TArray<uint8>& Buffer, int32 Size) const;
	void SetErrorMessage(const FString& Message);
	uint8 PeekParseMapState();

public:
	static constexpr size_t MAX_BINARY_LENGTH = 10 * 1024 * 1024; // 10 Mib
	static constexpr size_t MAX_STRING_LENGTH = 1 * 1024 * 1024; // 1 Mib

	explicit FMessagePackGameDataReader(FArchive* const Stream);

	virtual bool ReadNext() override;
	virtual const FString& GetIdentifier() const override;
	virtual const FString& GetValueAsString() const override;
	virtual double GetValueAsNumber() const override;
	virtual bool GetValueAsBoolean() const override;
	virtual const FString& GetErrorMessage() const override;
	virtual EJsonNotation GetNotation() override;
	virtual void SetErrorState(const FString& Message) override;
};
