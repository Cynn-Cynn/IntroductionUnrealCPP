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

	UFUNCTION(BlueprintCallable)
	void StartBezierInterpolation();

	UFUNCTION(BlueprintCallable)
	void RotateTo(FVector Rotation, float Duration);

	UFUNCTION(BlueprintCallable)
	void ScaleTo(FVector Scale, float Duration);

private:
	UStaticMeshComponent* CreateBezierPoint(const int& Index);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Visual")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Bezier")
	USceneComponent* BezierPointList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Bezier")
	float Duration;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Bezier")
	int PointCount;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Bezier")
	TArray<UStaticMeshComponent*> BezierPoint;

	USceneComponent* Root;
	float Timer;
	bool Interpolate;

	UStaticMesh* SphereMesh;
	TArray<FVector> PointLocations;
};
