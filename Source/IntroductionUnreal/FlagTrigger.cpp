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
	if (FlagManager != nullptr)
		FlagManager->OnFlagChanged.AddDynamic(this, &UFlagTrigger::CheckFlags);
}

void UFlagTrigger::BeginDestroy()
{
	Super::BeginDestroy();

	if (FlagManager != nullptr)
		FlagManager->OnFlagChanged.RemoveDynamic(this, &UFlagTrigger::CheckFlags);
}

bool UFlagTrigger::AreFlagsTriggered()
{
	if (FlagManager == nullptr)
		return false;

	for (FFlag Flag : Flags)
	{
		int FlagValue = FlagManager->GetFlagValue(Flag.FlagName);

		if (Flag.IsBitFlag)
		{
			int Bit = 1;
			Bit = Bit << Flag.FlagValue;
			if ((FlagValue & Bit) != Bit)
				return false;
		}
		else if (FlagValue == -1 || (FlagValue != Flag.FlagValue && Flag.IsExact) || (FlagValue < Flag.FlagValue && !Flag.IsExact))
		{
			return false;
		}
	}

	return true;
}

void UFlagTrigger::CheckFlags()
{
	if (AreFlagsTriggered())
		OnFlagValid.Broadcast();
	else
		OnFlagNotValid.Broadcast();
}

