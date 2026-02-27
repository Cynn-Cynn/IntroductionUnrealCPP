#include "MathsExamples.h"

AMathsExamples::AMathsExamples()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMathsExamples::BeginPlay()
{
	Super::BeginPlay();
	
	FVector;
	FQuat;
	FRotator;

	FQuat quat = FQuat::MakeFromEuler(FVector(0, 0, 0));
	quat = quat.Inverse();
	quat = quat * quat.Inverse();
	quat = FQuat::Identity;

	FRotator rotator = FRotator(0, 0, 0);
	rotator = rotator.GetInverse();
	rotator = FRotator::ZeroRotator;

	FVector vector = FVector();
	vector = quat.RotateVector(vector);
	vector = quat * vector;

	vector = rotator.RotateVector(vector);

	FMatrix transformMatrix = GetTransform().ToMatrixWithScale();
	FVector4 vector4 = FVector4();
	vector4 = transformMatrix.TransformFVector4(vector4);

	AddActorWorldOffset(FVector());
	AddActorWorldRotation(FRotator());
}

void AMathsExamples::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

