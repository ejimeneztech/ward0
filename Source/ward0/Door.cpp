#include "Door.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/Character.h"

ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = DoorMesh;
	DoorMesh->SetCollisionProfileName(TEXT("BlockAll"));
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
	StartRotation = GetActorRotation();
	TargetRotation = StartRotation;
}

void ADoor::Interact_Implementation(ACharacter* Interactor)
{
	if (bIsLocked)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Locked!"));
		return;
	}

	bIsOpen = !bIsOpen;

	if (bIsOpen)
	{
		FVector DoorToPlayer = Interactor->GetActorLocation() - GetActorLocation();
		FVector DoorForward = GetActorForwardVector();
		float DotProduct = FVector::DotProduct(DoorForward, DoorToPlayer);
		float Direction = DotProduct > 0 ? -1.0f : 1.0f;

		TargetRotation = StartRotation + FRotator(0.f, OpenAngle * Direction, 0.f);
	}
	else
	{
		TargetRotation = StartRotation;
	}
}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator CurrentRotation = GetActorRotation();

	FRotator NewRotation = FMath::RInterpConstantTo(
		CurrentRotation,
		TargetRotation,
		DeltaTime,
		OpenSpeed
	);

	SetActorRotation(NewRotation);
}