#include "Enemy.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::TakeDamage_Implementation(int Amount)
{
	CurrentHealth = FMath::Max(CurrentHealth - Amount, 0);
}

