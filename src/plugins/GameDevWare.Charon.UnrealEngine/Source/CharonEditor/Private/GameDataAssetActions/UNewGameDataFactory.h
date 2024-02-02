#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "UObject/ObjectMacros.h"
#include "UObject/UObjectGlobals.h"

#include "UNewGameDataFactory.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogUNewGameDataFactory, Log, All);

/*
 * Asset creation provider for UGameDataBase derived classes.
 */
UCLASS(CustomConstructor, CollapseCategories, ShowCategories=Object)
class CHARONEDITOR_API UNewGameDataFactory: public UFactory
{
	GENERATED_BODY()

public:
	explicit UNewGameDataFactory(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~ Begin UFactory Interface
	virtual bool ConfigureProperties() override;
	virtual bool DoesSupportClass(UClass* Class) override;
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	//~ End UFactory Interface
};

