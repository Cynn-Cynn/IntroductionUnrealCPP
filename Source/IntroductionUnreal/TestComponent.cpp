#include "TestComponent.h"

UTestComponent::UTestComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Duration = 0.0f;
	Timer = 0.0f;
	number = 0;
}

void UTestComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTestComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

