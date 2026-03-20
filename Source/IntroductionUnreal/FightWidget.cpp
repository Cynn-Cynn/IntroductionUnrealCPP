#include "FightWidget.h"

void UFightWidget::SetEndText(FString Text)
{
	EndText->SetText(FText::FromString(Text));
}

void UFightWidget::SetHealth(float Ratio)
{
	Health->SetPercent(Ratio);
}
