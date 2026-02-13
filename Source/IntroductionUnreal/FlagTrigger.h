#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FlagManager.h"
#include "IntroductionUnrealGameMode.h"
#include <Kismet/GameplayStatics.h>
#include "FlagTrigger.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INTRODUCTIONUNREAL_API UFlagTrigger : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFlagTrigger();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool AreFlagsTriggered();

private:
	UFUNCTION()
	void CheckFlags();

public:
	UPROPERTY(BlueprintAssignable)
	FFlagValueChanged OnFlagValid;

	UPROPERTY(BlueprintAssignable)
	FFlagValueChanged OnFlagNotValid;

protected:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

private:
	UPROPERTY(EditAnywhere)
	TArray<FFlag> Flags;

	UFlagManager* FlagManager;
};
