#include "GameHUD.h"

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	if (WidgetClass != nullptr)
	{
		InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), WidgetClass);
		InteractionWidget->AddToViewport();
	}
}

void AGameHUD::SetInteractionDescription(FString Description)
{
	InteractionWidget->SetText(Description);
}
