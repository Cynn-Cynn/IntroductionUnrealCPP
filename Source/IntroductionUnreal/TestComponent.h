#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TestComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INTRODUCTIONUNREAL_API UTestComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTestComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int number;

	float Timer;
};
