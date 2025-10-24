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
	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	void BezierInterpolation(const float& DeltaTime);
	void RotationInterpolation(const float& DeltaTime);
	void ScaleInterpolation(const float& DeltaTime);

	UFUNCTION(BlueprintCallable)
	void StartBezierInterpolation(float InterpDuration);

	UFUNCTION(BlueprintCallable)
	void RotateTo(FRotator Rotation, float InterpDuration);

	UFUNCTION(BlueprintCallable)
	void ScaleTo(FVector Scale, float InterpDuration);

private:
	UStaticMeshComponent* CreateBezierPoint(const int& Index);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Visual")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Bezier")
	USceneComponent* BezierPointList;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Bezier")
	int PointCount;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Bezier")
	TArray<UStaticMeshComponent*> BezierPoint;

	USceneComponent* Root;
	UStaticMesh* SphereMesh;

	float DurationBezier;
	float DurationRotation;
	float DurationScale;

	float TimerBezier;
	float TimerRotation;
	float TimerScale;

	bool bInterpolateBezier;
	bool bInterpolateRotation;
	bool bInterpolateScale;

	TArray<FVector> PointLocations;
	FRotator BaseRotation;
	FRotator TargetRotation;
	FVector BaseScale;
	FVector TargetScale;
};
