#include "MotionObject.h"

AMotionObject::AMotionObject()
{
	PrimaryActorTick.bCanEverTick = true;

	//Création de la racine de l'objet
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	//On crée le static mesh et on l'attache a la racine
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(Root);

	//On cherche le mesh du cube puis on le met dans le StaticMeshComponent
	static ConstructorHelpers::FObjectFinder<UStaticMesh> cubeMesh(TEXT("/Game/LevelPrototyping/Meshes/SM_Cube.SM_Cube"));
	if (cubeMesh.Succeeded())
		MeshComponent->SetStaticMesh(cubeMesh.Object);

	Duration = 0.0f;
	Timer = 0.0f;
	Points = TArray<FVector>();
	Interpolate = false;
}

void AMotionObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMotionObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Interpolate)
		return;

	Timer += DeltaTime;
	float Alpha = FMath::Clamp(Timer / Duration, 0, 1);

	FVector Location = UMyTools::BezierInterp(Points, Alpha);

	MeshComponent->SetWorldLocation(Location);
}

void AMotionObject::StartBezierInterpolation()
{
	Interpolate = true;
	Timer = 0.0f;
}

