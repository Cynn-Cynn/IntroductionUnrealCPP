#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MyHealth.generated.h"

UINTERFACE(MinimalAPI)
class UMyHealth : public UInterface
{
	GENERATED_BODY()
};

class INTRODUCTIONUNREAL_API IMyHealth
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void TakeDamage(int Amount);
};
