#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "IntroductionUnrealCharacter.h"
#include "Inspectable.generated.h"

UCLASS()
class INTRODUCTIONUNREAL_API AInspectable : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	AInspectable();

	void Interact_Implementation() override;
	FString GetDescription_Implementation() override;

	UFUNCTION(BlueprintCallable)
	void RotateInspectable(FVector2D MouseDelta);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float DistanceFromCamera;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
};
