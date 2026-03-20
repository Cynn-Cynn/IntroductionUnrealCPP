#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class INTRODUCTIONUNREAL_API IInteractable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Interact();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FString GetDescription();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ShowDescription(bool Value);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetWidgetRotation(FRotator Rotation);
};
