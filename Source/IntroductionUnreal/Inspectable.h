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

private:
	void StartInspection();
	void EndInspection();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float DistanceFromCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float InterpSpeed;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsInspected;

	FRotator CameraRotation;

	FVector InitialLocation;
	FRotator InitialRotation;

	FVector2D MouseInput;
};
