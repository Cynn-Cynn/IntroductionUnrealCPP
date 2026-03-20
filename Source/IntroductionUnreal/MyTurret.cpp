#include "MyTurret.h"

AMyTurret::AMyTurret()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Canon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Canon"));
	Canon->SetupAttachment(Mesh);

	Health = 10;
	Damage = 1;
	Timer = 0.0f;
}

void AMyTurret::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timer += DeltaTime;

	if (Timer >= 1.0f)
	{
		Shoot();
		Timer -= 1.0f;
	}
}

void AMyTurret::TakeDamage_Implementation(int Amount)
{
	if (Health <= Amount)
		Destroy();
}

void AMyTurret::Shoot()
{
	FHitResult Hit;
	FVector Start = Canon->GetComponentLocation();
	FVector End = Start + Canon->GetForwardVector() * 300.0f;
	ECollisionChannel Channel(ECC_GameTraceChannel1);
	const FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	if (GetWorld()->LineTraceSingleByChannel(OUT Hit, Start, End, Channel, TraceParams))
	{
		AActor* HitActor = Hit.GetActor();

		if (HitActor == nullptr)
			return;

		if (HitActor->Implements<UMyHealth>())
			IMyHealth::Execute_TakeDamage(HitActor, Damage);
	}
}

