#include "InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UInventoryComponent::AddItem(FItemData Item)
{
	if (Items.Num() >= MaxSlots)
	{
		return false;
	}

	Items.Add(Item);
	OnInventoryChanged.Broadcast();
	return true;
}

bool UInventoryComponent::RemoveItem(FName ItemID)
{
	for (int32 i = 0; i < Items.Num(); i++)
	{
		if (Items[i].ItemID == ItemID)
		{
			Items.RemoveAt(i);
			OnInventoryChanged.Broadcast();
			return true;
		}
	}
	return false;
}

bool UInventoryComponent::HasItem(FName ItemID) const
{
	for (const FItemData& Item : Items)
	{
		if (Item.ItemID == ItemID)
		{
			return true;
		}
	}
	return false;
}

TArray<FItemData> UInventoryComponent::GetItems() const
{
	return Items;
}

int32 UInventoryComponent::GetItemCount() const
{
	return Items.Num();
}