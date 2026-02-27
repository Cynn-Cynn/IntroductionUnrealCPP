#include "Inspectable.h"

AInspectable::AInspectable()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> cubeMesh(TEXT("/Game/LevelPrototyping/Meshes/SM_Cube.SM_Cube"));
	if (cubeMesh.Succeeded())
		Mesh->SetStaticMesh(cubeMesh.Object);

	DistanceFromCamera = 100.0f;
}

void AInspectable::Interact_Implementation()
{
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	if (Controller == nullptr)
		return;

	AIntroductionUnrealCharacter* Character = Cast<AIntroductionUnrealCharacter>(Controller->GetCharacter());
	if (Character != nullptr)
		Character->bCanMove = false;

	TObjectPtr<APlayerCameraManager> CameraManager = Controller->PlayerCameraManager;
	if (CameraManager == nullptr)
		return;

	FVector CameraLocation = CameraManager->GetCameraLocation();
	FRotator CameraRotation = CameraManager->GetCameraRotation();

	FVector InspectLocation = CameraLocation + CameraRotation.RotateVector(FVector::ForwardVector) * DistanceFromCamera;

	SetActorLocation(InspectLocation);
}

FString AInspectable::GetDescription_Implementation()
{
	return FString("Inspect");
}

void AInspectable::RotateInspectable(FVector2D MouseDelta)
{
}

void AInspectable::BeginPlay()
{
	Super::BeginPlay();
}

