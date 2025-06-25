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
	ConstructAddNewElementButton(VerticalBoxMain, DictionaryListView);
	ConstructSaveButton(VerticalBoxMain, DictionaryListView);
	
	ChildSlot
	[
		VerticalBoxMain
	];
	
}

void SDictionaryCreatorMainWindow::ConstructAddNewElementButton(TSharedRef<SVerticalBox> VerticalBox, TSharedRef<SDictionaryListView> DictionaryListView)
{
	VerticalBox->AddSlot()
	.AutoHeight()
	[
		SNew(SBox)
		.Padding(10.0f)
		.HeightOverride(40.0f)
		.WidthOverride(100.0f)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Top)
		[
			SNew(SButton)
			.ButtonColorAndOpacity(FLinearColor(0.2f, 0.9f, 0.2f, 1.0f))
			.Text(FText::FromString("Add element"))
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.OnClicked_Lambda([this, DictionaryListView]() ->FReply
			{
				DictionaryListView->Items.Add(MakeShared<FDictionaryElement>());
				DictionaryListView->ListView->RequestListRefresh();
				return FReply::Handled();
			})
		]
	];
}
void SDictionaryCreatorMainWindow::ConstructSaveButton(TSharedRef<SVerticalBox> VerticalBox, TSharedRef<SDictionaryListView> DictionaryListView)
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
			.OnClicked(this, &SDictionaryCreatorMainWindow::OnSaveButtonClicked, DictionaryListView->Items)
		]
	];
}
void SDictionaryCreatorMainWindow::ConstructSection(TSharedRef<SVerticalBox> VerticalBox, TSharedRef<SDictionaryListView> DictionaryListView, const FString& LabelText)
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

FReply SDictionaryCreatorMainWindow::OnSaveButtonClicked(TArray<TSharedPtr<FDictionaryElement>> Data)
{
	DictionaryCreatorUtils::ExportData(MainJSONObjectName,Data);
	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
