#include "InventoryWidget.h"
#include "Components/UniformGridPanel.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventoryWidget::InitializeInventory(UInventoryComponent* InInventoryComponent)
{
	InventoryComponent = InInventoryComponent;

	if (!InventoryComponent) return;

	// Listen for inventory changes
	InventoryComponent->OnInventoryChanged.AddDynamic(this, &UInventoryWidget::RefreshInventory);

	RefreshInventory();
}

void UInventoryWidget::RefreshInventory()
{
	if (!InventoryComponent) return;

	TArray<FItemData> Items = InventoryComponent->GetItems();

	for (int32 i = 0; i < Slots.Num(); i++)
	{
		if (i < Items.Num())
		{
			Slots[i]->SetItemData(Items[i]);
		}
		else
		{
			Slots[i]->SetEmpty();
		}
	}
}