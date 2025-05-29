// by Agnieszka Konopka, May 2025.

#include "SDictionaryCreatorMainWindow.h"

#include "DictionaryCreatorUtils.h"
#include "IPropertyTable.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDictionaryCreatorMainWindow::Construct(const FArguments& InArgs)
{
	TSharedRef<SVerticalBox> VerticalBoxMain = SNew(SVerticalBox);
	TSharedRef<SGridPanel> GridPanel = SNew(SGridPanel).FillColumn(0, 0.5f).FillColumn(1, 0.5f);
	AddHeaderText(GridPanel);
	for (int i = -1; i < DataArray.Num(); i++)
		AddDataRow(GridPanel, i + 1);
	AddElementButton(VerticalBoxMain, GridPanel);

	AddSection(VerticalBoxMain, GridPanel, TEXT("Data to save:"));
	AddSaveButton(VerticalBoxMain);
	
	ChildSlot
	[
		VerticalBoxMain
	];

	
}

void SDictionaryCreatorMainWindow::AddHeaderText(TSharedRef<SGridPanel> GridPanel)
{
	
}
void SDictionaryCreatorMainWindow::AddDataRow(TSharedRef<SGridPanel> GridPanel, uint32 Row)
{
	GridPanel->AddSlot(0, Row)
	.Padding(3)
	.HAlign(HAlign_Left)
		[
			SNew(SEditableTextBox)
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
			.OnTextCommitted_Lambda([this, Row](const FText& NewText, ETextCommit::Type CommitType)
			{
				this->UpdateDataArrayValue(Row, NewText);
			})
		];
	GridPanel->AddSlot(2, Row)
	.Padding(3)
	.HAlign(HAlign_Left)
	[
		SNew(SEditableTextBox)
	];
}
void SDictionaryCreatorMainWindow::AddElementButton(TSharedRef<SVerticalBox> VerticalBox, TSharedRef<SGridPanel> GridPanel)
{
	uint32 CurrentDataArraySize = DataArray.Num() + 1;
	VerticalBox->AddSlot().AutoHeight()
	[
		SNew(SBox).Padding(10.0f)
		[
			SNew(SButton).ButtonColorAndOpacity((FLinearColor(0.2f, 0.9f, 0.2f, 1.0f)))
			.Text(FText::FromString("Add element"))
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.OnClicked_Lambda([this, GridPanel, CurrentDataArraySize]() ->FReply
			{
				return this->AddElementButton(GridPanel, CurrentDataArraySize);
			})
		]
	];
}
void SDictionaryCreatorMainWindow::AddSaveButton(TSharedRef<SVerticalBox> VerticalBox)
{
	VerticalBox->AddSlot().AutoHeight()
	[
		SNew(SBox).Padding(10.0f)
		[
			SNew(SButton).ButtonColorAndOpacity((FLinearColor(0.2f, 0.9f, 0.2f, 1.0f)))
			.Text(FText::FromString("Save Data"))
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.OnClicked(this, &SDictionaryCreatorMainWindow::OnSaveButtonClicked)
		]
	];
}
void SDictionaryCreatorMainWindow::AddSection(TSharedRef<SVerticalBox> VerticalBox, TSharedRef<SGridPanel> GridPanel, const FString& LabelText)
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
	DictionaryCreatorUtils::ExportData(DataArray);
	return FReply::Handled();
}

FReply SDictionaryCreatorMainWindow::AddElementButton(TSharedRef<SGridPanel> GridPanel, uint32 Row)
{
	DataArray.Emplace("","");
	AddDataRow(GridPanel, Row);
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
