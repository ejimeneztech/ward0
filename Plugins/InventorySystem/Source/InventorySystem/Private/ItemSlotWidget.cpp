#include "ItemSlotWidget.h"

void UItemSlotWidget::SetItemData(const FItemData& Item)
{
	ItemData = Item;
	bIsEmpty = false;
}

void UItemSlotWidget::SetEmpty()
{
	ItemData = FItemData();
	bIsEmpty = true;
}