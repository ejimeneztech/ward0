#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Door.generated.h"

UCLASS()
class WARD0_API ADoor : public AActor, public IInteractable
{
	GENERATED_BODY()
    
public: 
	ADoor();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.0f;

	UPROPERTY(EditAnywhere)
	float OpenSpeed = 180.0f;

	UPROPERTY(EditAnywhere)
	bool bIsLocked = false;

	virtual void Interact_Implementation(ACharacter* Interactor) override;
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	bool bIsOpen = false;
	FRotator StartRotation;
	FRotator TargetRotation;
};