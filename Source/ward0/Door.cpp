#include "Door.h"
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
		TargetRotation = StartRotation + FRotator(0.f, OpenAngle, 0.f);
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