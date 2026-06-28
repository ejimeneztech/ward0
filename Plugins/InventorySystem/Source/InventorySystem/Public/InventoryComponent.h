#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FItemData.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChanged);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

	UPROPERTY(EditAnywhere, Category="Inventory")
	int32 MaxSlots = 20;

	UPROPERTY(BlueprintAssignable)
	FOnInventoryChanged OnInventoryChanged;

	UFUNCTION(BlueprintCallable)
	bool AddItem(FItemData Item);

	UFUNCTION(BlueprintCallable)
	bool RemoveItem(FName ItemID);

	UFUNCTION(BlueprintCallable)
	bool HasItem(FName ItemID) const;

	UFUNCTION(BlueprintCallable)
	TArray<FItemData> GetItems() const;

	UFUNCTION(BlueprintCallable)
	int32 GetItemCount() const;

private:
	UPROPERTY()
	TArray<FItemData> Items;
};