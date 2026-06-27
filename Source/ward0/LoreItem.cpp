#include "LoreItem.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

ALoreItem::ALoreItem()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetCollisionProfileName(TEXT("BlockAll"));
}

void ALoreItem::BeginPlay()
{
	Super::BeginPlay();
}

void ALoreItem::Interact_Implementation(ACharacter* Interactor)
{
	if (!LoreWidgetClass) return;

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PC) return;

	ULoreWidget* Widget = CreateWidget<ULoreWidget>(PC, LoreWidgetClass);
	if (Widget)
	{
		Widget->SetLoreContent(LoreTitle, LoreBody);
		Widget->AddToViewport();

		UGameplayStatics::SetGamePaused(GetWorld(), true);

		PC->SetInputMode(FInputModeUIOnly());
		PC->bShowMouseCursor = true;
	}
}