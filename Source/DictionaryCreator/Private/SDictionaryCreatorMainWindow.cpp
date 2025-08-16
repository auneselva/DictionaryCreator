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
	
	TSharedRef<SDictionaryListView> DictionaryListView = SNew(SDictionaryListView).Items({MakeShared<FDictionaryElement>()});
	ConstructSection(VerticalBoxMain, DictionaryListView, TEXT("Data to save:"));
	ConstructAddNewElementButtons(VerticalBoxMain, DictionaryListView);
	ConstructSaveButton(VerticalBoxMain, DictionaryListView);
	
	ChildSlot
	[
		VerticalBoxMain
	];
	
}

void SDictionaryCreatorMainWindow::ConstructAddNewElementButtons(TSharedRef<SVerticalBox> VerticalBox, TSharedRef<SDictionaryListView> DictionaryListView) const
{
	VerticalBox->AddSlot()
	.AutoHeight()
	[
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		.Padding(10.0f)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Top)
		[
			SNew(SButton)
			.ButtonColorAndOpacity(FLinearColor(0.2f, 0.9f, 0.2f, 1.0f))
			.Text(FText::FromString("Add element"))
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.DesiredSizeScale(FVector2D(1.5f,1.2f))
			.OnClicked_Lambda([this, DictionaryListView]() ->FReply
			{
				ConstructNewRow(DictionaryListView, 1);
				return FReply::Handled();
			})
		]
		+SHorizontalBox::Slot()
		.Padding(10.0f)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Top)
		[
			SNew(SButton)
			.ButtonColorAndOpacity(FLinearColor(0.2f, 0.9f, 0.2f, 1.0f))
			.Text(FText::FromString("Double them!"))
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.DesiredSizeScale(FVector2D(1.5f,1.2f))
			.OnClicked_Lambda([this, DictionaryListView]() ->FReply
			{
				ConstructNewRow(DictionaryListView, DictionaryListView->Items.Num());
				return FReply::Handled();
			})
		]
	];
}

void SDictionaryCreatorMainWindow::ConstructSaveButton(TSharedRef<SVerticalBox> VerticalBox, TSharedRef<SDictionaryListView> DictionaryListView) const
{
	VerticalBox->AddSlot()
	.VAlign(VAlign_Bottom)
	.AutoHeight()
	[
		SNew(SBox)
		.Padding(10.0f)
		.HeightOverride(60.0f)
		.WidthOverride(140.0f)
		.VAlign(VAlign_Bottom)
		.HAlign(HAlign_Center)
		[
			SNew(SButton)
			.ButtonColorAndOpacity(FLinearColor(0.9f, 0.6f, 0.1f, 1.0f))
			.Text(FText::FromString("Save Data"))
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.DesiredSizeScale(FVector2D(1.5f,1.2f))
			.OnClicked(this, &SDictionaryCreatorMainWindow::OnSaveButtonClicked, &DictionaryListView->Items)
		]
	];
}

void SDictionaryCreatorMainWindow::ConstructSection(TSharedRef<SVerticalBox> VerticalBox, TSharedRef<SDictionaryListView> DictionaryListView, const FString& LabelText) const
{
	VerticalBox->AddSlot()
	.FillHeight(0.8f)
	[
		SNew(SExpandableArea)
		.AreaTitle(FText::FromString(LabelText))
		.InitiallyCollapsed(false)
		.Padding(8)
		.BodyContent()
		[
			DictionaryListView
		]	
	];
}

FReply SDictionaryCreatorMainWindow::OnSaveButtonClicked(TArray<TSharedPtr<FDictionaryElement>>* Data) const
{
	DictionaryCreatorUtils::ExportData(MainJSONObjectName, *Data);
	return FReply::Handled();
}

void SDictionaryCreatorMainWindow::ConstructNewRow(TSharedRef<SDictionaryListView> DictionaryListView, uint32 nRows) const
{
	for (uint32 i = 0; i < nRows; i++)
		DictionaryListView->Items.Add(MakeShared<FDictionaryElement>());
	DictionaryListView->ListView->RequestListRefresh();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
