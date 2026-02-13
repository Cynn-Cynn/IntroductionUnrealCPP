#include "FlagTrigger.h"

UFlagTrigger::UFlagTrigger()
{
	PrimaryComponentTick.bCanEverTick = false;

	FlagManager = nullptr;
}

void UFlagTrigger::BeginPlay()
{
	Super::BeginPlay();

	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	AIntroductionUnrealGameMode* GameMode = Cast<AIntroductionUnrealGameMode>(GameModeBase);
	if (GameMode == nullptr)
		return;

	FlagManager = GameMode->GetComponentByClass<UFlagManager>();
}

bool UFlagTrigger::AreFlagsTriggered()
{
	if (FlagManager == nullptr)
		return false;

	for (FFlag Flag : Flags)
	{
		int FlagValue = FlagManager->GetFlagValue(Flag.FlagName);
		if (FlagValue == -1 || FlagValue != Flag.FlagValue)
			return false;
	}

	return true;
}

