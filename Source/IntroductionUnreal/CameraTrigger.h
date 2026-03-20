#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Camera/CameraComponent.h>
#include <Components/BoxComponent.h>
#include <TopViewCharacter.h>
#include "CameraTrigger.generated.h"

UCLASS()
class INTRODUCTIONUNREAL_API ACameraTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ACameraTrigger();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void ChangeCamera(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	void ChangeCameraAfterFade();

	void EnableCamera(UCameraComponent* CameraComponent, bool bActivate);

private:
	UPROPERTY(meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* Trigger;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	bool bDefaultCamera;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	bool bFade;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float FadeDuration;

	FTimerHandle CameraFade;

	static UCameraComponent* ActiveCamera;
};
