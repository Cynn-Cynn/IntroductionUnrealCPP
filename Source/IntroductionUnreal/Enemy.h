#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Health.h"
#include "Enemy.generated.h"

UCLASS()
class INTRODUCTIONUNREAL_API AEnemy : public AActor, public IHealth
{
	GENERATED_BODY()
	
public:	
	AEnemy();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void TakeDamage_Implementation(int Amount) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int MaxHealth;
};
