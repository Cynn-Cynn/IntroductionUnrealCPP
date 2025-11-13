#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interactable.h"
#include "Camera/CameraComponent.h"
#include "PlayerInteraction.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INTRODUCTIONUNREAL_API UPlayerInteraction : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerInteraction();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void GetInteractableObject();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float DetectionRange;

	UCameraComponent* Camera;
};
