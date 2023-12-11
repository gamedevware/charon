#pragma once

#include "IGameDataReader.h"

#include "Containers/Array.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "Containers/UnrealString.h"
#include "Templates/SharedPointer.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonTypes.h"

/*
 * Token based reader for dynamic FJsonObject object as source of token stream.
 * Provides generalized IGameDataReader behaviour for already de-serialized objects.
 * Used for patching FJsonObject and TryLoad from resulting merged FJsonObject.
 */
class UECHARON_API FJsonObjectGameDataReader final : public IGameDataReader
{
private:
	class FJsonObjectReaderFrame
	{
	private:
		bool MemberNameIsVisited;
		size_t CurrentIndex;
		TArray<TSharedPtr<FJsonValue>>* CurrentArray;
		TArray<FString> CurrentObjectKeys;
		TSharedPtr<FJsonObject>* CurrentObject;

	public:
		explicit FJsonObjectReaderFrame(TSharedPtr<FJsonObject>& JsonObject);
		explicit FJsonObjectReaderFrame(TArray<TSharedPtr<FJsonValue>>& JsonObject);

		FString& GetCurrentMemberName();
		TSharedPtr<FJsonValue> GetCurrentValue();
		EJson GetContainerToken() const;

		void NextMemberOrItem();
		EJsonToken GetNextJsonToken();
	};

	TSharedPtr<FJsonObject> JsonObject;
	TArray<FJsonObjectReaderFrame> Frames;
	EJsonNotation Notation;
	EJsonToken CurrentToken;
	FString Identifier;
	FString ErrorMessage;
	FString StringValue;
	double NumberValue;
	bool BoolValue;
	bool FinishedReadingRootObject;

public:
	explicit FJsonObjectGameDataReader(const TSharedPtr<FJsonObject>& JsonObject);

	virtual bool ReadNext() override;
	virtual const FString& GetIdentifier() const override;
	virtual const FString& GetValueAsString() const override;
	virtual double GetValueAsNumber() const override;
	virtual bool GetValueAsBoolean() const override;
	virtual const FString& GetErrorMessage() const override;
	virtual EJsonNotation GetNotation() override;
	virtual void SetErrorState(const FString& Message) override;

	// TODO Should override SkipAny for efficient skipping big JsonObject trees
};
