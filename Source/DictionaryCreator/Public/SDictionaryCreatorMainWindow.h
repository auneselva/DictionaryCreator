// by Agnieszka Konopka, May 2025.

#pragma once

#include "SDictionaryListView.h"
#include "Widgets/SCompoundWidget.h"

class DICTIONARYCREATOR_API SDictionaryCreatorMainWindow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDictionaryCreatorMainWindow) {}
		
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	
	void ConstructAddNewElementButton(TSharedRef<SVerticalBox> VerticalBox, TSharedRef<SDictionaryListView> DictionaryListView);
	void ConstructSaveButton(TSharedRef<SVerticalBox> VerticalBox, TSharedRef<SDictionaryListView> DictionaryListView);
	void ConstructSection(TSharedRef<SVerticalBox> VerticalBox, TSharedRef<SDictionaryListView> ListView, const FString& LabelText);

	FReply OnSaveButtonClicked(TArray<TSharedPtr<FDictionaryElement>>* Data);
protected:
	
	TArray<TPair<FString, FString>> DataArray;
	TArray<TSharedPtr<FDictionaryElement>> ListViewDataArray;
	const static FString MainJSONObjectName;
};
