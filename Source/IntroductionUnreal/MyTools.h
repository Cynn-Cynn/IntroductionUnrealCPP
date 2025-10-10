#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyTools.generated.h" //Toujours en dernier

UCLASS()
class INTRODUCTIONUNREAL_API UMyTools : public UObject
{
	//On y touche pas
	GENERATED_BODY()

public:
	static void DebugLog(const FString& Message);
	static void DebugLogWarning(const FString& Message);
	static void DebugLogError(const FString& Message);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MyTools")
	static FVector MyUnclampedLerp(const FVector A, FVector B, float T);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MyTools")
	static float MyClamp(float Value, float Min, float Max);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MyTools")
	static FVector MyLerp(FVector A, FVector B, float T);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MyTools")
	static FVector BezierInterp(const TArray<FVector>& Points, float Alpha);
};
