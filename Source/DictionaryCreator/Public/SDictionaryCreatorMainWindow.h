// Copyright https://github.com/auneselva

#pragma once

#include "SDictionaryListView.h"
#include "Widgets/SCompoundWidget.h"

class DICTIONARYCREATOR_API SDictionaryCreatorMainWindow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDictionaryCreatorMainWindow) {}
		
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	
protected:
	
	const static FString MainJSONObjectName;
	
	void ConstructAddNewElementButtons(TSharedRef<SVerticalBox> VerticalBox, TSharedRef<SDictionaryListView> DictionaryListView) const;
	void ConstructSaveButton(TSharedRef<SVerticalBox> VerticalBox, TSharedRef<SDictionaryListView> DictionaryListView) const;
	void ConstructSection(TSharedRef<SVerticalBox> VerticalBox, TSharedRef<SDictionaryListView> ListView, const FString& LabelText) const;
	FReply OnSaveButtonClicked(TArray<TSharedPtr<FDictionaryElement>>* Data) const;

	void ConstructNewRow(TSharedRef<SDictionaryListView> DictionaryListView, uint32 nRows) const;
};
