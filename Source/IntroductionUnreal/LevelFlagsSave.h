#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LevelFlagsSave.generated.h"

UCLASS()
class INTRODUCTIONUNREAL_API ULevelFlagsSave : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray<FString> FlagNames;
	UPROPERTY()
	TArray<int> FlagValues;
};
