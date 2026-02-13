#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Flag.h"
#include "FlagManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INTRODUCTIONUNREAL_API UFlagManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFlagManager();

	UFUNCTION(BlueprintCallable)
	int GetFlagValue(FGameplayTag FlagName) const;

	UFUNCTION(BlueprintCallable)
	void SetFlag(FGameplayTag FlagName, int FlagValue);

	UFUNCTION(BlueprintCallable)
	void IncrementFlag(FGameplayTag FlagName);

	UFUNCTION(BlueprintCallable)
	void DecrementFlag(FGameplayTag FlagName);

	UFUNCTION(BlueprintCallable)
	void FlipFlag(FGameplayTag FlagName);

	UFUNCTION(BlueprintCallable)
	void ResetFlag(FGameplayTag FlagName);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayTagContainer FlagNames;

	TMap<FGameplayTag, FFlag> Flags;
};
