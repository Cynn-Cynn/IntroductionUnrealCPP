#include "Turret.h"

ATurret::ATurret()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();
}

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATurret::ApplyDamage(AActor* Entity, int Amount)
{
	if (Entity->GetClass()->ImplementsInterface(UHealth::StaticClass()))
		IHealth::Execute_TakeDamage(Entity, Amount);
}

