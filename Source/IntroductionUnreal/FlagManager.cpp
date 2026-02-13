#include "FlagManager.h"

UFlagManager::UFlagManager()
{
	PrimaryComponentTick.bCanEverTick = false;

	Flags = TMap<FGameplayTag, FFlag>();
}

int UFlagManager::GetFlagValue(FGameplayTag FlagName) const
{
	if (Flags.Contains(FlagName))
		return Flags[FlagName].FlagValue;

	UE_LOG(LogTemp, Error, TEXT("Get | Flag not found: %s"), *FlagName.ToString());
	return -1;
}

void UFlagManager::SetFlag(FGameplayTag FlagName, int FlagValue)
{
	if (!Flags.Contains(FlagName))
	{
		UE_LOG(LogTemp, Error, TEXT("Set | Flag not found: %s"), *FlagName.ToString());
		return;
	}

	if (FlagValue < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Set | Negative flag value: %d"), FlagValue);
		return;
	}

	Flags[FlagName].FlagValue = FlagValue;
}

void UFlagManager::IncrementFlag(FGameplayTag FlagName)
{
	if (!Flags.Contains(FlagName))
	{
		UE_LOG(LogTemp, Error, TEXT("Increment | Flag not found: %s"), *FlagName.ToString());
		return;
	}

	Flags[FlagName].FlagValue += 1;
}

void UFlagManager::DecrementFlag(FGameplayTag FlagName)
{
	if (!Flags.Contains(FlagName))
	{
		UE_LOG(LogTemp, Error, TEXT("Decrement | Flag not found: %s"), *FlagName.ToString());
		return;
	}

	if (Flags[FlagName].FlagValue > 0)
		Flags[FlagName].FlagValue -= 1;
}

void UFlagManager::FlipFlag(FGameplayTag FlagName)
{
	if (!Flags.Contains(FlagName))
	{
		UE_LOG(LogTemp, Error, TEXT("Flip | Flag not found: %s"), *FlagName.ToString());
		return;
	}

	if (Flags[FlagName].FlagValue == 0)
		Flags[FlagName].FlagValue = 1;
	else if (Flags[FlagName].FlagValue == 1)
		Flags[FlagName].FlagValue = 0;
	else
		UE_LOG(LogTemp, Error, TEXT("Flip | Try to flip a non boolean flag: %s"), *FlagName.ToString());
}

void UFlagManager::ResetFlag(FGameplayTag FlagName)
{
	if (!Flags.Contains(FlagName))
	{
		UE_LOG(LogTemp, Error, TEXT("Reset | Flag not found: %s"), *FlagName.ToString());
		return;
	}

	Flags[FlagName].FlagValue = 0;
}

void UFlagManager::BeginPlay()
{
	Super::BeginPlay();

	for (FGameplayTag Tag : FlagNames.GetGameplayTagArray())
	{
		FFlag Flag = FFlag(Tag, 0);
		Flags.Add(Tag, Flag);
	}
}

