#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyHealth.h"
#include "MyTurret.generated.h"

UCLASS()
class INTRODUCTIONUNREAL_API AMyTurret : public AActor, public IMyHealth
{
	GENERATED_BODY()
	
public:	
	AMyTurret();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void TakeDamage_Implementation(int Amount) override;
	
private:
	void Shoot();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Canon;

	UPROPERTY(EditAnywhere)
	int Health;

	UPROPERTY(EditAnywhere)
	int Damage;

	float Timer;
};
