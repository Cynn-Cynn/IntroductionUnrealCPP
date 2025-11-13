#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExerciceInterface.h"
#include "ExerciceActor.generated.h"

UCLASS()
class INTRODUCTIONUNREAL_API AExerciceActor : public AActor, public IExerciceInterface
{
	GENERATED_BODY()
	
public:	
	AExerciceActor();

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	virtual void Tick(float DeltaTime) override;
	const FVector GetLocation_Implementation() override;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Mesh")
	bool SwitchMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Mesh")
	UStaticMeshComponent* MeshRenderer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Mesh")
	AActor* OtherActor;

	UStaticMesh* CubeMesh;
	UStaticMesh* SphereMesh;

	USceneComponent* Root;
};
