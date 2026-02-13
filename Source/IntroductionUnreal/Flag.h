#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Flag.generated.h"

USTRUCT(BlueprintType)
struct INTRODUCTIONUNREAL_API FFlag
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag FlagName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int FlagValue;
};
