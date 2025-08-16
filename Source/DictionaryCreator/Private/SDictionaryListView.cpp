// Copyright https://github.com/auneselva

#include "SDictionaryListView.h"

void SDictionaryElementRow::Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable)
{
	ItemPtr = InArgs._ItemPtr;
	OnGenerateWidgetForColumn = InArgs._OnGenerateWidgetForColumn;
	check(ItemPtr.IsValid());

	SMultiColumnTableRow<TSharedPtr<FDictionaryElement>>::Construct(FSuperRowType::FArguments(), OwnerTable);
}

TSharedRef<SWidget> SDictionaryElementRow::GenerateWidgetForColumn(const FName& InColumnName) 
{
	if (OnGenerateWidgetForColumn.IsBound())
	{
		return OnGenerateWidgetForColumn.Execute(ItemPtr, InColumnName);
	}
	return SNullWidget::NullWidget;
}

void SDictionaryListView::Construct(const FArguments& InArgs)
{
	Items = InArgs._Items;
	ChildSlot
	[
		SAssignNew(ListView, SListView<TSharedPtr<FDictionaryElement>>)
		.ListItemsSource(&Items)
		.OnGenerateRow(this, &SDictionaryListView::GenerateRow)
		.HeaderRow
		(
			SNew(SHeaderRow)
			+ SHeaderRow::Column("Element")
			.DefaultLabel(FText::FromString("Duplicated keys will not be stored!"))
		)
	];
}

TSharedRef<ITableRow> SDictionaryListView::GenerateRow(TSharedPtr<FDictionaryElement> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	TSharedRef<SDictionaryElementRow> Row = SNew(SDictionaryElementRow, OwnerTable)
		.ItemPtr(Item)
		.OnGenerateWidgetForColumn(this, &SDictionaryListView::GenerateWidgetForColumn);
	return Row;
}

TSharedRef<SWidget> SDictionaryListView::GenerateWidgetForColumn(TSharedPtr<FDictionaryElement> Item, const FName& InColumnName)
{
	return SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.Padding(2)
		.HAlign(HAlign_Left)
		.FillWidth(0.3f)
		[
			SNew(SEditableTextBox)
			.HintText(FText::FromString("Key"))
			.Text(FText::FromString(Item->Key))
			.MinDesiredWidth(400.0f)
			.OnTextCommitted_Lambda([Item](const FText& NewText, ETextCommit::Type CommitType)
			{
				Item->UpdateDataArrayKey(NewText);
			})
		]
	+ SHorizontalBox::Slot()
		.Padding(2)
		.HAlign(HAlign_Left)
		.FillWidth(0.6f)
		[
			SNew(SEditableTextBox)
			.HintText(FText::FromString("Value"))
			.Text(FText::FromString(Item->Key))
			.MinDesiredWidth(1500.0f)
			.OnTextCommitted_Lambda([Item](const FText& NewText, ETextCommit::Type CommitType)
			{
				Item->UpdateDataArrayValue(NewText);
			})
		]
	+ SHorizontalBox::Slot() 
		.Padding(3)
		.HAlign(HAlign_Center)
		.FillWidth(0.1f)
		[
			SNew(SBox)
			.Padding(2.0f)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.WidthOverride(40.0f)
			[
				SNew(SButton)
				.ButtonColorAndOpacity(FLinearColor(0.6f, 0.6, 0.6f, 1.0f))
				.Text(FText::FromString("-"))
				.ToolTipText(FText::FromString("Remove row"))
				.OnClicked_Lambda([this, Item]() ->FReply
				{
					this->Items.Remove(Item);
					this->ListView->RequestListRefresh();
					return FReply::Handled();
				})
			]
	];
}