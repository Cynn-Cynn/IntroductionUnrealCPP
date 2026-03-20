#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "IntroductionUnrealCharacter.h"
#include "Components/WidgetComponent.h"
#include "InteractionWidget.h"
#include "Inspectable.generated.h"

UCLASS()
class INTRODUCTIONUNREAL_API AInspectable : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	AInspectable();

	void Interact_Implementation() override;
	FString GetDescription_Implementation() override;
	void ShowDescription_Implementation(bool Value) override;
	void SetWidgetRotation_Implementation(FRotator Rotation) override;

	UFUNCTION(BlueprintCallable)
	void RotateInspectable(FVector2D MouseDelta);

protected:
	UFUNCTION(BlueprintCallable)
	void BeginPlay() override;

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

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* DescriptiondWidget;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsInspected;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FString DescriptionText;

	FRotator CameraRotation;

	FVector InitialLocation;
	FRotator InitialRotation;

	FVector2D MouseInput;

	UInteractionWidget* InteractionWidget;
};
