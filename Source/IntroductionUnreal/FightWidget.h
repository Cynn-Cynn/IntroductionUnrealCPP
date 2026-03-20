#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include <Components/ProgressBar.h>
#include "FightWidget.generated.h"

UCLASS()
class INTRODUCTIONUNREAL_API UFightWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetEndText(FString Text);
	UFUNCTION(BlueprintCallable)
	void SetHealth(float Ratio);

public:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* EndText;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UProgressBar* Health;
};
