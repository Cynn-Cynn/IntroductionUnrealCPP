#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "FlagManager.h"
#include "IntroductionUnrealGameMode.h"
#include <Kismet/GameplayStatics.h>
#include "PickupKey.generated.h"

UCLASS()
class INTRODUCTIONUNREAL_API APickupKey : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	APickupKey();

	UFUNCTION(BlueprintCallable)
	void Interact_Implementation() override;

	UFUNCTION(BlueprintCallable)
	FString GetDescription_Implementation() override;

private:
	UPROPERTY(EditAnywhere)
	FGameplayTag Flag;
};
