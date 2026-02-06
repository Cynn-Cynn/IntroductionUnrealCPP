#include "TestInteraction.h"

ATestInteraction::ATestInteraction()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> cubeMesh(TEXT("/Game/LevelPrototyping/Meshes/SM_Cube.SM_Cube"));
	if (cubeMesh.Succeeded())
		MeshComponent->SetStaticMesh(cubeMesh.Object);
}

void ATestInteraction::Interact_Implementation()
{
	MeshComponent->AddLocalRotation(FRotator(0.0f, 10.0f, 0.0f));
}

FString ATestInteraction::GetDescription_Implementation()
{
	return FString("Rotate");
}

