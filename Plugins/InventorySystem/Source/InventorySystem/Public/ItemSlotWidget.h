#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FItemData.h"
#include "ItemSlotWidget.generated.h"

UCLASS()
class INVENTORYSYSTEM_API UItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetItemData(const FItemData& Item);

	UFUNCTION(BlueprintCallable)
	void SetEmpty();

	UPROPERTY(BlueprintReadOnly)
	FItemData ItemData;

	UPROPERTY(BlueprintReadOnly)
	bool bIsEmpty = true;
};