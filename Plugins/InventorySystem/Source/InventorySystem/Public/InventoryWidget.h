#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryComponent.h"
#include "ItemSlotWidget.h"
#include "InventoryWidget.generated.h"

UCLASS()
class INVENTORYSYSTEM_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void InitializeInventory(UInventoryComponent* InInventoryComponent);

	UFUNCTION(BlueprintCallable)
	void RefreshInventory();

	UPROPERTY(EditAnywhere, Category="Inventory")
	TSubclassOf<UItemSlotWidget> ItemSlotWidgetClass;

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY()
	UInventoryComponent* InventoryComponent;

	UPROPERTY()
	TArray<UItemSlotWidget*> Slots;
};