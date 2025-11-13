#include "ExerciceActor.h"

AExerciceActor::AExerciceActor()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshFinder(TEXT("/Engine/EditorMeshes/EditorCube.EditorCube"));
	if (CubeMeshFinder.Succeeded())
		CubeMesh = CubeMeshFinder.Object;
	else
		CubeMesh = nullptr;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshFinder(TEXT("/Engine/EditorMeshes/EditorSphere.EditorSphere"));
	if (SphereMeshFinder.Succeeded())
		SphereMesh = SphereMeshFinder.Object;
	else
		SphereMesh = nullptr;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	MeshRenderer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Renderer"));
	MeshRenderer->SetStaticMesh(CubeMesh);
	MeshRenderer->SetupAttachment(Root);

	OtherActor = nullptr;
}

void AExerciceActor::BeginPlay()
{
	Super::BeginPlay();

	if (OtherActor != nullptr && OtherActor->GetClass()->ImplementsInterface(UExerciceInterface::StaticClass()))
	{
		FVector Location = IExerciceInterface::Execute_GetLocation(OtherActor);
		MeshRenderer->SetWorldLocation(Location);
	}
}

void AExerciceActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (SwitchMesh)
		MeshRenderer->SetStaticMesh(SphereMesh);
	else
		MeshRenderer->SetStaticMesh(CubeMesh);
}

void AExerciceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

const FVector AExerciceActor::GetLocation_Implementation()
{
	return MeshRenderer->GetComponentLocation();
}

