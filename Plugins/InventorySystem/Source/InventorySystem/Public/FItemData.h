#pragma once

#include "CoreMinimal.h"
#include "FItemData.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Key,
	Consumable,
	Weapon,
	Quest,
	Misc
};

USTRUCT(BlueprintType)
struct INVENTORYSYSTEM_API FItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* ItemIcon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType ItemType = EItemType::Misc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity = 1;
};