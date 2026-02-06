#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InteractionWidget.h"
#include "GameHUD.generated.h"

UCLASS()
class INTRODUCTIONUNREAL_API AGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetInteractionDescription(FString Description);

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UInteractionWidget> WidgetClass;

	UInteractionWidget* InteractionWidget;
};
