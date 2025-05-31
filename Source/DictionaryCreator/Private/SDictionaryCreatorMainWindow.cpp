// by Agnieszka Konopka, May 2025.

#include "SDictionaryCreatorMainWindow.h"

#include "DictionaryCreatorUtils.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION


const FString SDictionaryCreatorMainWindow::MainJSONObjectName = TEXT("DictionaryJsonObject");

void SDictionaryCreatorMainWindow::Construct(const FArguments& InArgs)
{
	TSharedRef<SVerticalBox> VerticalBoxMain = SNew(SVerticalBox);
	TSharedRef<SGridPanel> GridPanel = SNew(SGridPanel).FillColumn(0, 0.3f).FillColumn(1, 0.6f).FillColumn(2, 0.1f);
	
	// add one empty row if there are none yet
	if (DataArray.IsEmpty())
		DataArray.Emplace("","");
	for (int i = 0; i < DataArray.Num(); i++)
		ConstructDataRow(GridPanel, i);
	ConstructSection(VerticalBoxMain, GridPanel, TEXT("Data to save:"));
	ConstructAddNewElementButton(VerticalBoxMain, GridPanel);
	ConstructSaveButton(VerticalBoxMain);
	
	ChildSlot
	[
		VerticalBoxMain
	];

	
}

void SDictionaryCreatorMainWindow::ConstructDataRow(TSharedRef<SGridPanel> GridPanel, uint32 Row)
{
	GridPanel->AddSlot(0, Row)
	.Padding(3)
	.HAlign(HAlign_Left)
		[
			SNew(SEditableTextBox)
			.HintText(FText::FromString("Key"))
			.MinDesiredWidth(80.0f)
			.OnTextCommitted_Lambda([this, Row](const FText& NewText, ETextCommit::Type CommitType)
			{
				this->UpdateDataArrayKey(Row, NewText);
			})
		];
	GridPanel->AddSlot(1, Row)
		.Padding(3)
		.HAlign(HAlign_Left)
		[
			SNew(SEditableTextBox)
			.HintText(FText::FromString("Value"))
			.MinDesiredWidth(200.0f)
			.OnTextCommitted_Lambda([this, Row](const FText& NewText, ETextCommit::Type CommitType)
			{
				this->UpdateDataArrayValue(Row, NewText);
			})
		];
	GridPanel->AddSlot(2, Row)
	.Padding(3)
	.HAlign(HAlign_Right)
	[
		SNew(SBox).Padding(2.0f)
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			.WidthOverride(40.0f)
		[
			SNew(SButton)
			.ButtonColorAndOpacity((FLinearColor(0.6f, 0.6, 0.6f, 1.0f)))
			.Text(FText::FromString("-"))
			.OnClicked_Lambda([this, Row]() ->FReply
			{
				return this->RemoveData(Row);
			})
		]
	];
}
void SDictionaryCreatorMainWindow::ConstructAddNewElementButton(TSharedRef<SVerticalBox> VerticalBox, TSharedRef<SGridPanel> GridPanel)
{
	VerticalBox->AddSlot().AutoHeight()
	[
		SNew(SBox).Padding(10.0f).Padding(10.0f).HeightOverride(60.0f).WidthOverride(120.0f).HAlign(HAlign_Center).VAlign(VAlign_Top)
		[
			SNew(SButton)
			.ButtonColorAndOpacity((FLinearColor(0.2f, 0.9f, 0.2f, 1.0f)))
			.Text(FText::FromString("Add element"))
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.OnClicked_Lambda([this, GridPanel]() ->FReply
			{
				return this->AddNewData(GridPanel);
			})
		]
	];
}
void SDictionaryCreatorMainWindow::ConstructSaveButton(TSharedRef<SVerticalBox> VerticalBox)
{
	VerticalBox->AddSlot().VAlign(VAlign_Bottom)
	[
		SNew(SBox).Padding(10.0f).HeightOverride(80.0f).WidthOverride(160.0f)
		[
			SNew(SButton)
			.ButtonColorAndOpacity((FLinearColor(0.9f, 0.6f, 0.1f, 1.0f)))
			.Text(FText::FromString("Save Data"))
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.OnClicked(this, &SDictionaryCreatorMainWindow::OnSaveButtonClicked)
		]
	];
}
void SDictionaryCreatorMainWindow::ConstructSection(TSharedRef<SVerticalBox> VerticalBox, TSharedRef<SGridPanel> GridPanel, const FString& LabelText)
{
	VerticalBox->AddSlot().AutoHeight()
	[
		SNew(SExpandableArea)
		.AreaTitle(FText::FromString(LabelText))
		.InitiallyCollapsed(false)
		.Padding(8)
		.BodyContent()
		[
			GridPanel
		]
	];
}

FReply SDictionaryCreatorMainWindow::OnSaveButtonClicked()
{
	DictionaryCreatorUtils::ExportData(MainJSONObjectName,DataArray);
	return FReply::Handled();
}

FReply SDictionaryCreatorMainWindow::AddNewData(TSharedRef<SGridPanel> GridPanel)
{
	DataArray.Emplace("","");
	ConstructDataRow(GridPanel, DataArray.Num() - 1);
	return FReply::Handled();
}

FReply SDictionaryCreatorMainWindow::RemoveData(int32 Row)
{
	if (Row >= 0 && Row < DataArray.Num())
	{
		DataArray.Remove(DataArray[Row]);
	}
	
	//rebuild widget
	return FReply::Handled();
}

void SDictionaryCreatorMainWindow::UpdateDataArrayKey(int32 Index, const FText& NewKey)
{
	if (Index < 0 || Index > DataArray.Num() - 1)
		return;
	DataArray[Index].Key = NewKey.ToString();
}

void SDictionaryCreatorMainWindow::UpdateDataArrayValue(int32 Index, const FText& NewValue)
{
	if (Index < 0 || Index > DataArray.Num() - 1)
		return;
	DataArray[Index].Value = NewValue.ToString();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
