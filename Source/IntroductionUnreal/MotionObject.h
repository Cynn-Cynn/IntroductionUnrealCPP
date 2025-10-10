#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyTools.h"
#include "MotionObject.generated.h"

UCLASS()
class INTRODUCTIONUNREAL_API AMotionObject : public AActor
{
	GENERATED_BODY()
	
public:	
	AMotionObject();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void StartBezierInterpolation();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Bezier")
	float Duration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Bezier")
	TArray<FVector> Points;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Visual")
	UStaticMeshComponent* MeshComponent;

	USceneComponent* Root;
	float Timer;
	bool Interpolate;
};
