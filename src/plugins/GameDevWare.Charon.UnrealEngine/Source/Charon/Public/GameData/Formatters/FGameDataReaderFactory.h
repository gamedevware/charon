#pragma once
#include "FJsonGameDataReader.h"
#include "FJsonObjectGameDataReader.h"
#include "FMessagePackGameDataReader.h"
#include "IGameDataReader.h"

#include "Templates/SharedPointer.h"
#include "Serialization/Archive.h"
#include "Dom/JsonObject.h"

/*
 * Factory class for creating various format readers for UGameDataBase::TryLoad methods.
 */
class FGameDataReaderFactory
{
public:
	static TSharedRef<IGameDataReader> CreateJsonReader(FArchive* const Stream)
	{
		return MakeShareable(new FJsonGameDataReader(Stream));
	}
	static TSharedRef<IGameDataReader> CreateMessagePackReader(FArchive* const Stream)
	{
		return MakeShareable(new FMessagePackGameDataReader(Stream));
	}
	static TSharedRef<IGameDataReader> CreateJsonObjectReader(const TSharedPtr<FJsonObject>& JsonObject)
	{
		return MakeShareable(new FJsonObjectGameDataReader(JsonObject));
	}
};
