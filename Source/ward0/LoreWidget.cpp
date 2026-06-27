#include "LoreWidget.h"
#include "Kismet/GameplayStatics.h"

void ULoreWidget::SetLoreContent(const FText& Title, const FText& Body)
{
	LoreTitle = Title;
	LoreBody = Body;
}

void ULoreWidget::CloseWidget()
{
	RemoveFromViewport();

	UGameplayStatics::SetGamePaused(GetWorld(), false);

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->SetInputMode(FInputModeGameOnly());
		PC->bShowMouseCursor = false;
	}
}