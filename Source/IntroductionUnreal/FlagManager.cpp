#include "FlagManager.h"

UFlagManager::UFlagManager()
{
	PrimaryComponentTick.bCanEverTick = false;

	Flags = TMap<FGameplayTag, int>();
}

int UFlagManager::GetFlagValue(FGameplayTag FlagName) const
{
	if (Flags.Contains(FlagName))
		return Flags[FlagName];

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

	Flags[FlagName] = FlagValue;
	OnFlagChanged.Broadcast();
}

void UFlagManager::IncrementFlag(FGameplayTag FlagName)
{
	if (!Flags.Contains(FlagName))
	{
		UE_LOG(LogTemp, Error, TEXT("Increment | Flag not found: %s"), *FlagName.ToString());
		return;
	}

	Flags[FlagName] += 1;
	OnFlagChanged.Broadcast();
}

void UFlagManager::DecrementFlag(FGameplayTag FlagName)
{
	if (!Flags.Contains(FlagName))
	{
		UE_LOG(LogTemp, Error, TEXT("Decrement | Flag not found: %s"), *FlagName.ToString());
		return;
	}

	if (Flags[FlagName] > 0)
	{
		Flags[FlagName] -= 1;
		OnFlagChanged.Broadcast();
	}
}

void UFlagManager::FlipFlag(FGameplayTag FlagName)
{
	if (!Flags.Contains(FlagName))
	{
		UE_LOG(LogTemp, Error, TEXT("Flip | Flag not found: %s"), *FlagName.ToString());
		return;
	}

	if (Flags[FlagName] == 0)
	{
		Flags[FlagName] = 1;
		OnFlagChanged.Broadcast();

	}
	else if (Flags[FlagName] == 1)
	{
		Flags[FlagName] = 0;
		OnFlagChanged.Broadcast();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Flip | Try to flip a non boolean flag: %s"), *FlagName.ToString());
	}
}

void UFlagManager::FlipBitFlag(FGameplayTag FlagName, int Index)
{
	if (!Flags.Contains(FlagName))
	{
		UE_LOG(LogTemp, Error, TEXT("Bit Flip | Flag not found: %s"), *FlagName.ToString());
		return;
	}

	if (Index >= 32)
	{
		UE_LOG(LogTemp, Error, TEXT("Bit Flip | Invalid index: %d"), Index);
		return;
	}

	int Bit = 1;
	Bit = Bit << Index;
	Flags[FlagName] ^= Bit;
}

void UFlagManager::ResetFlag(FGameplayTag FlagName)
{
	if (!Flags.Contains(FlagName))
	{
		UE_LOG(LogTemp, Error, TEXT("Reset | Flag not found: %s"), *FlagName.ToString());
		return;
	}

	Flags[FlagName] = 0;
	OnFlagChanged.Broadcast();
}

void UFlagManager::LoadLevelFlags(int LevelIndex)
{
	FString LevelName = FString(LEVEL_SAVE).Append(FString::FromInt(LevelIndex));
	ULevelFlagsSave* Save = Cast<ULevelFlagsSave>(UGameplayStatics::LoadGameFromSlot(LevelName, 0));

	if (Save == nullptr)
		return;

	for (int i = 0; i < Save->FlagNames.Num(); i++)
	{
		FGameplayTag FlagName = FGameplayTag::RequestGameplayTag(FName(Save->FlagNames[i]), false);
		SetFlag(FlagName, Save->FlagValues[i]);
	}

	SetFlag(LevelIndexTag, LevelIndex);
}

void UFlagManager::SaveLevelFlags()
{
	int LevelIndex = GetFlagValue(LevelIndexTag);

	ULevelFlagsSave* Save = Cast<ULevelFlagsSave>(UGameplayStatics::CreateSaveGameObject(ULevelFlagsSave::StaticClass()));

	TArray<FGameplayTag> FlagsArray;
	Flags.GetKeys(FlagsArray);
	for (FGameplayTag Flag : FlagsArray)
	{
		if (Flag.ToString().Contains("Level."))
		{
			Save->FlagNames.Add(Flag.ToString());
			Save->FlagValues.Add(Flags[Flag]);
		}
	}

	FString LevelName = FString(LEVEL_SAVE).Append(FString::FromInt(LevelIndex));
	UGameplayStatics::SaveGameToSlot(Save, LevelName, 0);
}

void UFlagManager::LoadPlayerFlags()
{
	UPlayerValuesSave* Save = Cast<UPlayerValuesSave>(UGameplayStatics::LoadGameFromSlot(PLAYER_SAVE, 0));

	if (Save == nullptr)
		return;

	SetFlag(LevelIndexTag, Save->LevelIndex);

	LoadLevelFlags(Save->LevelIndex);
}

void UFlagManager::SavePlayerFlags()
{
	UPlayerValuesSave* Save = Cast<UPlayerValuesSave>(UGameplayStatics::CreateSaveGameObject(UPlayerValuesSave::StaticClass()));

	TArray<FGameplayTag> FlagsArray;
	Flags.GetKeys(FlagsArray);
	for (FGameplayTag Flag : FlagsArray)
	{
		if (Flag.ToString().Contains("Player."))
		{
			if (Flag.ToString().Contains("LevelIndex"))
			{
				Save->LevelIndex = GetFlagValue(Flag);
			}

			//Other player variables
		}
	}

	UGameplayStatics::SaveGameToSlot(Save, PLAYER_SAVE, 0);
}

void UFlagManager::BeginPlay()
{
	Super::BeginPlay();

	for (FGameplayTag Tag : FlagNames.GetGameplayTagArray())
	{
		Flags.Add(Tag, 0);
	}

	LevelIndexTag = FGameplayTag::RequestGameplayTag("Player.LevelIndex");
}

