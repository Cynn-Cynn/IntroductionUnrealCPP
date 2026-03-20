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

	UFUNCTION(BlueprintCallable)
	void ShowDescription_Implementation(bool Value) override;
	UFUNCTION(BlueprintCallable)
	void SetWidgetRotation_Implementation(FRotator Rotation) override;

private:
	UPROPERTY(EditAnywhere)
	FGameplayTag Flag;

	UPROPERTY(EditAnywhere)
	int FlagIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Visual")
	UStaticMeshComponent* MeshComponent;
};
