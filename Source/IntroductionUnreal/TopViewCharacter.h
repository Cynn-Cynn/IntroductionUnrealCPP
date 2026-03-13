#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Camera/CameraComponent.h>
#include "EnhancedInputComponent.h"
#include "TopViewCharacter.generated.h"

UCLASS()
class INTRODUCTIONUNREAL_API ATopViewCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATopViewCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveInput(const FInputActionValue& Value);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* MainCamera;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
};
