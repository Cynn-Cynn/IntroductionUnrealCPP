#include "InteractionWidget.h"

void UInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//InteractionText = Cast<UTextBlock>(GetWidgetFromName("InteractionText"));
}

void UInteractionWidget::SetText(FString Text)
{
	InteractionText->SetText(FText::FromString(Text));
}