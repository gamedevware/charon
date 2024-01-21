#include "GameData/UGameDataBase.h"

#include "GameData/UGameDataImportData.h"

void UGameDataBase::PostInitProperties()
{
#if WITH_EDITORONLY_DATA
	if (!HasAnyFlags(RF_ClassDefaultObject | RF_NeedLoad))
	{
		AssetImportData = NewObject<UGameDataImportData>(this, TEXT("GameDataImportData"));
		AssetImportData->AddFileName(FString(), 0); // add empty filename for now
	}
#endif
	Super::PostInitProperties();
}

void UGameDataBase::PostLoad()
{
	Super::PostLoad();

#if WITH_EDITORONLY_DATA
	if (Cast<UGameDataImportData>(AssetImportData) == nullptr)
	{
		AssetImportData = NewObject<UGameDataImportData>(this, TEXT("GameDataImportData"));
	}
#endif
}
