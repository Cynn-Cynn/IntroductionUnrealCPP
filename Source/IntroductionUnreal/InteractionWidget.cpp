#include "InteractionWidget.h"

void UInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//InteractionText = Cast<UTextBlock>(GetWidgetFromName("InteractionText"));
}

void UInteractionWidget::SetText(FString Text)
{
	if (Text != InteractionText->Text.ToString())
		InteractionText->SetText(FText::FromString(Text));
}