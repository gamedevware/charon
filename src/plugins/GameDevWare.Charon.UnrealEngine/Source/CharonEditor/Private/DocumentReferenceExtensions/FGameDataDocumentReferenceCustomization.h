#pragma once

#include "GameData/UGameDataBase.h"
#include "PropertyEditor/Public/IPropertyTypeCustomization.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFGameDataDocumentReferenceCustomization, Log, All);

/*
 * FGameDataDocumentReference custom editor with Schema/Id selection combo boxes. 
 */
class FGameDataDocumentReferenceCustomization : public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	// BEGIN IPropertyTypeCustomization interface
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
	// END IPropertyTypeCustomization interface

	/** Handle to the struct properties being customized */
	TSharedPtr<IPropertyHandle> GameDataPropertyHandle;
	TSharedPtr<IPropertyHandle> SchemaPropertyHandle;
	TSharedPtr<IPropertyHandle> IdPropertyHandle;
	/** The MetaData derived filter for the row type */
private:
	UGameDataBase* GetGameData() const;
	
	void OnGetDocumentIds(TArray< TSharedPtr<FString> >& OutStrings, TArray<TSharedPtr<SToolTip>>& OutToolTips, TArray<bool>& OutRestrictedItems) const;
	FString OnGetCurrentDocumentIdString() const;

	void OnGetSchemaNames(TArray< TSharedPtr<FString> >& OutStrings, TArray<TSharedPtr<SToolTip>>& OutToolTips, TArray<bool>& OutRestrictedItems) const;
	FString OnGetCurrentSchemaNameString() const;
};
