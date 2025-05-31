// by Agnieszka Konopka, May 2025.

#pragma once

#include "Widgets/SCompoundWidget.h"

class DICTIONARYCREATOR_API SDictionaryCreatorMainWindow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDictionaryCreatorMainWindow) {}
		
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	//virtual void RebuildW
	
	void ConstructDataRow(TSharedRef<SGridPanel> GridPanel, uint32 Row);
	void ConstructAddNewElementButton(TSharedRef<SVerticalBox> VerticalBox, TSharedRef<SGridPanel> GridPanel);
	void ConstructSaveButton(TSharedRef<SVerticalBox> VerticalBox);
	void ConstructSection(TSharedRef<SVerticalBox> VerticalBox, TSharedRef<SGridPanel> GridPanel, const FString& LabelText);

	FReply AddNewData(TSharedRef<SGridPanel> GridPanel);
	FReply RemoveData(int32 Row);
	FReply OnSaveButtonClicked();

	
	void UpdateDataArrayKey(int32 Index, const FText& NewKey);
	void UpdateDataArrayValue(int32 Index, const FText& NewValue);

private:
	
	TArray<TPair<FString, FString>> DataArray;
	const static FString MainJSONObjectName;
};
