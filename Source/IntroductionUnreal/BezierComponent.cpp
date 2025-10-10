#include "BezierComponent.h"

UBezierComponent::UBezierComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Duration = 0.0f;
	Timer = 0.0f;
	Points = TArray<FVector>();
	Owner = nullptr;
}


void UBezierComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
}


void UBezierComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Timer += DeltaTime;
	float Alpha = FMath::Clamp(Timer / Duration, 0, 1);

	FVector Location = UMyTools::BezierInterp(Points, Alpha);

	Owner->SetActorLocation(Location);
}

