#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoreWidget.generated.h"

UCLASS()
class WARD0_API ULoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetLoreContent(const FText& Title, const FText& Body);

	UFUNCTION(BlueprintCallable)
	void CloseWidget();

	UPROPERTY(BlueprintReadOnly)
	FText LoreTitle;

	UPROPERTY(BlueprintReadOnly)
	FText LoreBody;
};