#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MathsExamples.generated.h"

UCLASS()
class INTRODUCTIONUNREAL_API AMathsExamples : public AActor
{
	GENERATED_BODY()
	
public:	
	AMathsExamples();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
