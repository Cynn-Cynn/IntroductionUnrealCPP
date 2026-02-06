#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "TestInteraction.generated.h"

UCLASS()
class INTRODUCTIONUNREAL_API ATestInteraction : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	ATestInteraction();

	UFUNCTION(BlueprintCallable)
	void Interact_Implementation() override;

	UFUNCTION(BlueprintCallable)
	FString GetDescription_Implementation() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Visual")
	UStaticMeshComponent* MeshComponent;
};
