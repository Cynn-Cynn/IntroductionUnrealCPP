#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Health.h"
#include "Turret.generated.h"

UCLASS()
class INTRODUCTIONUNREAL_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	ATurret();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void ApplyDamage(AActor* Entity, int Amount);
};
