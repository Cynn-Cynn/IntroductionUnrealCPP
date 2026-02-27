#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Flag.h"
#include "LevelFlagsSave.h"
#include <Kismet/GameplayStatics.h>
#include "FlagManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFlagValueChanged);

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
	void FlipBitFlag(FGameplayTag FlagName, int Index);

	UFUNCTION(BlueprintCallable)
	void ResetFlag(FGameplayTag FlagName);

	UFUNCTION(BlueprintCallable)
	void LoadLevelFlags(int LevelIndex);

	UFUNCTION(BlueprintCallable)
	void SaveLevelFlags(int LevelIndex);

public:
	UPROPERTY(BlueprintAssignable)
	FFlagValueChanged OnFlagChanged;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayTagContainer FlagNames;

	TMap<FGameplayTag, int> Flags;

};
