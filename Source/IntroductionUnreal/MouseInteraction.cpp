#include "MouseInteraction.h"

AMouseInteraction::AMouseInteraction()
{
	PrimaryActorTick.bCanEverTick = true;

	Controller = nullptr;
}

void AMouseInteraction::BeginPlay()
{
	Super::BeginPlay();

	Controller = GetWorld()->GetFirstPlayerController();

	if (Controller != nullptr)
		Controller->bShowMouseCursor = true;
}

void AMouseInteraction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TraceFromMouse();
}

void AMouseInteraction::TraceFromMouse()
{
	if (Controller == nullptr)
		return;

	FVector MouseLocation = FVector();
	FVector MouseDirection = FVector();
	if (Controller->DeprojectMousePositionToWorld(MouseLocation, MouseDirection))
	{
		FHitResult Hit;
		FVector Start = MouseLocation;
		FVector End = MouseLocation + MouseDirection * 1000.0f;
		ECollisionChannel Channel(ECC_GameTraceChannel1);
		const FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

		if (GetWorld()->LineTraceSingleByChannel(OUT Hit, Start, End, Channel, TraceParams))
		{
			AActor* HitActor = Hit.GetActor();

			if (HitActor != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("%s"), *HitActor->GetName());
				DrawDebugSphere(GetWorld(), Hit.Location, 10.0f, 12, FColor::Red);
			}
		}

		DrawDebugLine(GetWorld(), Start, End, FColor::Red);
	}
}

