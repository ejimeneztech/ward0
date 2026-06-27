#include "ward0Character.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interactable.h"
#include "DrawDebugHelpers.h"
#include "Engine/LocalPlayer.h"
#include "ward0.h"

Award0Character::Award0Character()
{
    PrimaryActorTick.bCanEverTick = false;

    GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

    FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));
    FirstPersonMesh->SetupAttachment(GetMesh());
    FirstPersonMesh->SetOnlyOwnerSee(true);
    FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
    FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));

    FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
    FirstPersonCameraComponent->SetupAttachment(FirstPersonMesh, FName("head"));
    FirstPersonCameraComponent->SetRelativeLocationAndRotation(FVector(-2.8f, 5.89f, 0.0f), FRotator(0.0f, 90.0f, -90.0f));
    FirstPersonCameraComponent->bUsePawnControlRotation = true;
    FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
    FirstPersonCameraComponent->bEnableFirstPersonScale = true;
    FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
    FirstPersonCameraComponent->FirstPersonScale = 0.6f;

    GetMesh()->SetOwnerNoSee(true);
    GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;
    GetCapsuleComponent()->SetCapsuleSize(34.0f, 96.0f);

    GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
    GetCharacterMovement()->AirControl = 0.5f;
}

void Award0Character::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }
}

void Award0Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &Award0Character::DoJumpStart);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &Award0Character::DoJumpEnd);
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &Award0Character::MoveInput);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &Award0Character::LookInput);
        EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &Award0Character::LookInput);
        EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &Award0Character::Interact);
    }
    else
    {
        UE_LOG(Logward0, Error, TEXT("'%s' Failed to find an Enhanced Input Component!"), *GetNameSafe(this));
    }
}

void Award0Character::MoveInput(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();
    DoMove(MovementVector.X, MovementVector.Y);
}

void Award0Character::LookInput(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();
    DoAim(LookAxisVector.X, LookAxisVector.Y);
}

void Award0Character::DoAim(float Yaw, float Pitch)
{
    if (GetController())
    {
        AddControllerYawInput(Yaw);
        AddControllerPitchInput(Pitch);
    }
}

void Award0Character::DoMove(float Right, float Forward)
{
    if (GetController())
    {
        AddMovementInput(GetActorRightVector(), Right);
        AddMovementInput(GetActorForwardVector(), Forward);
    }
}

void Award0Character::DoJumpStart()
{
    Jump();
}

void Award0Character::DoJumpEnd()
{
    StopJumping();
}

void Award0Character::Interact()
{
    PerformInteractionTrace();
}

void Award0Character::PerformInteractionTrace()
{
    FVector Start = FirstPersonCameraComponent->GetComponentLocation();
    FVector End = Start + (FirstPersonCameraComponent->GetForwardVector() * InteractionRange);

    FHitResult HitResult;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        Start,
        End,
        ECC_Visibility,
        Params
    );

    if (bHit)
    {
        AActor* HitActor = HitResult.GetActor();
        if (HitActor && HitActor->Implements<UInteractable>())
        {
            IInteractable::Execute_Interact(HitActor, Cast<ACharacter>(this));
        }
    }
}