#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MouseInteraction.generated.h"

UCLASS()
class INTRODUCTIONUNREAL_API AMouseInteraction : public AActor
{
	GENERATED_BODY()
	
public:	
	AMouseInteraction();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	void TraceFromMouse();

private:
	APlayerController* Controller;
};
