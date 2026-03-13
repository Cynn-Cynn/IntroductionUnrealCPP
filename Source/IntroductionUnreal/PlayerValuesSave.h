#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PlayerValuesSave.generated.h"

UCLASS()
class INTRODUCTIONUNREAL_API UPlayerValuesSave : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	int LevelIndex;
};
