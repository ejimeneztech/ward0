#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "LoreWidget.h"
#include "LoreItem.generated.h"

UCLASS()
class WARD0_API ALoreItem : public AActor, public IInteractable
{
	GENERATED_BODY()
    
public: 
	ALoreItem();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category="Lore")
	FText LoreTitle;

	UPROPERTY(EditAnywhere, Category="Lore", meta=(MultiLine=true))
	FText LoreBody;

	UPROPERTY(EditAnywhere, Category="Lore")
	TSubclassOf<ULoreWidget> LoreWidgetClass;

	virtual void Interact_Implementation(ACharacter* Interactor) override;

protected:
	virtual void BeginPlay() override;
};