#include "PickupKey.h"

APickupKey::APickupKey()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APickupKey::Interact_Implementation()
{
	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	AIntroductionUnrealGameMode* GameMode = Cast<AIntroductionUnrealGameMode>(GameModeBase);
	if (GameMode == nullptr)
		return;

	UFlagManager* FlagManager = GameMode->GetComponentByClass<UFlagManager>();
	if (FlagManager == nullptr)
		return;

	FlagManager->IncrementFlag(Flag);
	Destroy();
}

FString APickupKey::GetDescription_Implementation()
{
	return FString("Pickup");
}

