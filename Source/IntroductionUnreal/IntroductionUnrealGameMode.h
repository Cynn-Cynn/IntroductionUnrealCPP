// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "IntroductionUnrealGameMode.generated.h"

/**
 *  Simple GameMode for a first person game
 */
UCLASS(abstract)
class AIntroductionUnrealGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AIntroductionUnrealGameMode();

private:
	void Test(float a);
};



