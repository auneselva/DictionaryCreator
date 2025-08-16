// Copyright https://github.com/auneselva

#pragma once

#include "DictionaryElement.h"

class SDictionaryElementRow : public SMultiColumnTableRow<TSharedPtr<FDictionaryElement>>
{
	DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<SWidget>, FOnGenerateWidgetForColumn, TSharedPtr<FDictionaryElement>, const FName&);
	SLATE_BEGIN_ARGS(SDictionaryElementRow) {}
	SLATE_ARGUMENT(TSharedPtr<FDictionaryElement>, ItemPtr);
	SLATE_EVENT(FOnGenerateWidgetForColumn, OnGenerateWidgetForColumn)
SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable);
	virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;

private:
	TSharedPtr<FDictionaryElement> ItemPtr;
	FOnGenerateWidgetForColumn OnGenerateWidgetForColumn;
};

class SDictionaryListView : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDictionaryListView): _Items() {}
	SLATE_ARGUMENT(TArray<TSharedPtr<FDictionaryElement>>, Items);
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	TSharedPtr<SListView<TSharedPtr<FDictionaryElement>>> ListView;
	TArray<TSharedPtr<FDictionaryElement>> Items;
	
private:
	TSharedRef<ITableRow> GenerateRow(TSharedPtr<FDictionaryElement> Item, const TSharedRef<STableViewBase>& OwnerTable);
	TSharedRef<SWidget> GenerateWidgetForColumn(TSharedPtr<FDictionaryElement> Item, const FName& InColumnName);
};