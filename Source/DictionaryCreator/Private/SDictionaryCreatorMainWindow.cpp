// by Agnieszka Konopka, May 2025.

#include "SDictionaryCreatorMainWindow.h"

#include "DictionaryCreatorUtils.h"
#include "SlateOptMacros.h"

DEFINE_LOG_CATEGORY_STATIC(LogSDictionaryCreatorMainWindow, Log, All);

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
		ConstructDataRow(GridPanel, i, FText::FromString(DataArray[i].Key),FText::FromString(DataArray[i].Value));
	ConstructSection(VerticalBoxMain, GridPanel, TEXT("Data to save:"));
	ConstructAddNewElementButton(VerticalBoxMain, GridPanel);
	ConstructSaveButton(VerticalBoxMain);
	
	ChildSlot
	[
		VerticalBoxMain
	];
	
}

void SDictionaryCreatorMainWindow::ConstructDataRow(TSharedRef<SGridPanel> GridPanel, int32 Row, const FText& InTextKey, const FText& InTextValue)
{
	GridPanel->AddSlot(0, Row)
	.Padding(3)
	.HAlign(HAlign_Left)
		[
			SNew(SEditableTextBox)
			.HintText(FText::FromString("Key"))
			.Text(InTextKey)
			.MinDesiredWidth(90.0f)
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
			.Text(InTextValue)
			.MinDesiredWidth(300.0f)
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
			.OnClicked_Lambda([this, GridPanel, Row]() ->FReply
			{
				return this->RemoveData(GridPanel, Row);
			})
		]
	];
}
void SDictionaryCreatorMainWindow::ConstructAddNewElementButton(TSharedRef<SVerticalBox> VerticalBox, TSharedRef<SGridPanel> GridPanel)
{
	VerticalBox->AddSlot().AutoHeight()
	[
		SNew(SBox).Padding(10.0f).Padding(10.0f).HeightOverride(40.0f).WidthOverride(100.0f).HAlign(HAlign_Center).VAlign(VAlign_Top)
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
		SNew(SBox).Padding(10.0f).HeightOverride(60.0f).WidthOverride(140.0f).VAlign(VAlign_Bottom).HAlign(HAlign_Center)
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

FReply SDictionaryCreatorMainWindow::RemoveData(TSharedRef<SGridPanel> GridPanel, int32 Row)
{
	if (Row < 0 || Row > DataArray.Num() - 1)
	{
		UE_LOG(LogSDictionaryCreatorMainWindow, Warning, TEXT("No row %d in the Panel to remove. Something went wrong."), Row);
		return FReply::Unhandled();
	}

	DataArray.RemoveAt(Row);
	GridPanel->ClearChildren();
	if (DataArray.IsEmpty())
		DataArray.Emplace("","");
	for (int i = 0; i < DataArray.Num(); i++)
		ConstructDataRow(GridPanel, i, FText::FromString(DataArray[i].Key),FText::FromString(DataArray[i].Value));
	
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
