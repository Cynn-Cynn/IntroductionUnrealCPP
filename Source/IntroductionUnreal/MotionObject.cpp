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

	//Bezier
	PointCount = 0;
	PointLocations = TArray<FVector>();
	TimerBezier = 0.0f;
	DurationBezier = 0.0f;
	bInterpolateBezier = false;

	//Rotation
	BaseRotation = FRotator();
	TargetRotation = FRotator();
	TimerRotation = 0.0f;
	DurationRotation = 0.0f;
	bInterpolateRotation = false;

	//Scale
	BaseScale = FVector();
	TargetScale = FVector();
	TimerScale = 0.0f;
	DurationScale = 0.0f;
	bInterpolateScale = false;
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

	BezierInterpolation(DeltaTime);
	RotationInterpolation(DeltaTime);
	ScaleInterpolation(DeltaTime);
}

void AMotionObject::BezierInterpolation(const float& DeltaTime)
{
	//On vérifie si l'interpolation est lancée
	if (!bInterpolateBezier)
		return;

	//On augmente le timer grace au delta time
	TimerBezier += DeltaTime;
	//On détermine l'alpha qui permet de faire l'interpolation par rapport au temps écoulé
	float Alpha = FMath::Clamp(TimerBezier / DurationBezier, 0.0f, 1.0f);

	//On effectue l'interpolation avec les points de bezier
	FVector Location = UMyTools::BezierInterp(PointLocations, Alpha);

	//On applique la location à l'objet
	MeshComponent->SetWorldLocation(Location);
}

void AMotionObject::RotationInterpolation(const float& DeltaTime)
{
	if (!bInterpolateRotation)
		return;

	TimerRotation += DeltaTime;
	float Alpha = FMath::Clamp(TimerRotation / DurationRotation, 0.0f, 1.0f);

	FRotator Rotation = FMath::Lerp(BaseRotation, TargetRotation, Alpha);

	MeshComponent->SetWorldRotation(Rotation);
}

void AMotionObject::ScaleInterpolation(const float& DeltaTime)
{
	if (!bInterpolateScale)
		return;

	TimerScale += DeltaTime;
	float Alpha = FMath::Clamp(TimerScale / DurationScale, 0.0f, 1.0f);

	FVector Scale = FMath::Lerp(BaseScale, TargetScale, Alpha);

	MeshComponent->SetWorldScale3D(Scale);
}

void AMotionObject::StartBezierInterpolation(float InterpDuration)
{
	bInterpolateBezier = true;
	TimerBezier = 0.0f;
	DurationBezier = InterpDuration;
	
	PointLocations = TArray<FVector>();

	for (int i = 0; i < PointCount; i++)
	{
		PointLocations.Add(BezierPoint[i]->GetComponentLocation());
	}
}

void AMotionObject::RotateTo(FRotator Rotation, float InterpDuration)
{
	bInterpolateRotation = true;
	BaseRotation = MeshComponent->GetComponentRotation();
	TargetRotation = Rotation;
	TimerRotation = 0.0f;
	DurationRotation = InterpDuration;
}

void AMotionObject::ScaleTo(FVector Scale, float InterpDuration)
{
	bInterpolateScale = true;
	BaseScale = MeshComponent->GetComponentScale();
	TargetScale = Scale;
	TimerScale = 0.0f;
	DurationScale = InterpDuration;
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

