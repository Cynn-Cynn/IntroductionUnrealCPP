#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyTools.h"
#include "BezierComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INTRODUCTIONUNREAL_API UBezierComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBezierComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Duration;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TArray<FVector> Points;

private:
	AActor* Owner;
	float Timer;
};
