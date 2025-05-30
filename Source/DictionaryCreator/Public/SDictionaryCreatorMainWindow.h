// by Agnieszka Konopka, May 2025.

#pragma once

#include "Widgets/SCompoundWidget.h"

class DICTIONARYCREATOR_API SDictionaryCreatorMainWindow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDictionaryCreatorMainWindow) {}
		
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	void AddHeaderText(TSharedRef<SGridPanel> GridPanel);
	void AddDataRow(TSharedRef<SGridPanel> GridPanel, uint32 Row);
	void AddElementButton(TSharedRef<SVerticalBox> VerticalBox, TSharedRef<SGridPanel> GridPanel);
	void AddSaveButton(TSharedRef<SVerticalBox> VerticalBox);
	void AddSection(TSharedRef<SVerticalBox> VerticalBox, TSharedRef<SGridPanel> GridPanel, const FString& LabelText);

	FReply AddNewData(TSharedRef<SGridPanel> GridPanel);
	FReply RemoveData(uint32 Row);
	FReply OnSaveButtonClicked();

	
	void UpdateDataArrayKey(int32 Index, const FText& NewKey);
	void UpdateDataArrayValue(int32 Index, const FText& NewValue);

private:
	
	TArray<TPair<FString, FString>> DataArray;
	const static FString MainJSONObjectName;
};
