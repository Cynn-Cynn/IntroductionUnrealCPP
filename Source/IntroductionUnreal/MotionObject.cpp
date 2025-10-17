#include "MotionObject.h"

AMotionObject::AMotionObject()
{
	PrimaryActorTick.bCanEverTick = true;

	//Création de la racine de l'objet
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	BezierPointList = CreateDefaultSubobject<USceneComponent>(TEXT("Bezier Point List"));
	BezierPointList->SetupAttachment(Root);

	//On crée le static mesh et on l'attache a la racine
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(Root);

	//On cherche le mesh du cube puis on le met dans le StaticMeshComponent
	static ConstructorHelpers::FObjectFinder<UStaticMesh> cubeMesh(TEXT("/Game/LevelPrototyping/Meshes/SM_Cube.SM_Cube"));
	if (cubeMesh.Succeeded())
		MeshComponent->SetStaticMesh(cubeMesh.Object);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> sphereMeshFinder(TEXT("/Game/LevelPrototyping/Meshes/SM_ChamferCube.SM_ChamferCube"));
	if (sphereMeshFinder.Succeeded())
		SphereMesh = sphereMeshFinder.Object;
	else
		SphereMesh = nullptr;

	PointCount = 0;
	Duration = 0.0f;
	Timer = 0.0f;
	PointLocations = TArray<FVector>();
	Interpolate = false;
}

void AMotionObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMotionObject::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	int PointCountDelta = PointCount - BezierPoint.Num();

	if (PointCountDelta == 0)
		return;

	if (PointCountDelta > 0)
	{
		//Créer des points
		for (int i = 0; i < PointCountDelta; i++)
		{
			BezierPoint.Add(CreateBezierPoint(BezierPoint.Num()));
		}
	}
	else
	{
		//Détruire des points
		for (int i = BezierPoint.Num() - 1; i >= PointCount; i--)
		{
			UStaticMeshComponent* Point = BezierPoint.Pop();
			Point->DestroyComponent();
		}
	}
}

void AMotionObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Interpolate)
		return;

	Timer += DeltaTime;
	float Alpha = FMath::Clamp(Timer / Duration, 0, 1);

	FVector Location = UMyTools::BezierInterp(PointLocations, Alpha);

	MeshComponent->SetWorldLocation(Location);
}

void AMotionObject::StartBezierInterpolation()
{
	Interpolate = true;
	Timer = 0.0f;
	
	PointLocations = TArray<FVector>();

	for (int i = 0; i < PointCount; i++)
	{
		PointLocations.Add(BezierPoint[i]->GetComponentLocation());
	}
}

void AMotionObject::RotateTo(FVector Rotation, float Duration)
{
}

void AMotionObject::ScaleTo(FVector Scale, float Duration)
{
}

UStaticMeshComponent* AMotionObject::CreateBezierPoint(const int& Index)
{
	//On créer le composant
	FName PointName = FName("Point_" + FString::FromInt(Index + 1));
	UStaticMeshComponent* Point = NewObject<UStaticMeshComponent>(this, PointName);

	//On notifie à l'objet que le composant appartient à l'objet
	Point->RegisterComponent();

	//AttachToComponent
	Point->AttachToComponent(BezierPointList, FAttachmentTransformRules::KeepRelativeTransform);

	Point->SetStaticMesh(SphereMesh);
	Point->bHiddenInGame = true;
	Point->SetCollisionProfileName("NoCollision");
	Point->SetWorldScale3D(FVector(0.1f)); //FVector(0.1f, 0.1f, 0.1f)

	return Point;
}

