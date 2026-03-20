#include "Inspectable.h"

AInspectable::AInspectable()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> cubeMesh(TEXT("/Game/LevelPrototyping/Meshes/SM_Cube.SM_Cube"));
	if (cubeMesh.Succeeded())
		Mesh->SetStaticMesh(cubeMesh.Object);

	DescriptiondWidget = CreateDefaultSubobject<UWidgetComponent>("Description");
	DescriptiondWidget->SetupAttachment(RootComponent);

	DistanceFromCamera = 100.0f;
	InterpSpeed = 0.5f;
	RotationSpeed = 180.0f;
	CameraRotation = FRotator();
	IsInspected = false;
	InitialLocation = FVector();
	InitialRotation = FRotator();
	MouseInput = FVector2D();

	InteractionWidget = nullptr;
	DescriptionText = "Interact";
}

void AInspectable::Interact_Implementation()
{
	if (IsInspected)
		EndInspection();
	else
		StartInspection();
}

FString AInspectable::GetDescription_Implementation()
{
	return IsInspected ? FString("") : FString("Inspect");
}

void AInspectable::ShowDescription_Implementation(bool Value)
{
	InteractionWidget->SetText(Value ? DescriptionText : "");
}

void AInspectable::SetWidgetRotation_Implementation(FRotator Rotation)
{
	DescriptiondWidget->SetWorldRotation(Rotation);
	DescriptiondWidget->AddLocalRotation(FRotator(0.0f, 180.0f, 0.0f));
}

void AInspectable::RotateInspectable(FVector2D MouseDelta)
{
	UWorld* World = GetWorld();
	if (World == nullptr)
		return;

	float DeltaTime = World->GetDeltaSeconds();

	MouseInput = FMath::Vector2DInterpTo(MouseInput, MouseDelta, DeltaTime, InterpSpeed);

	FVector VerticalRotation = CameraRotation.RotateVector(FVector(MouseInput.Y, 0.0f, 0.0f));
	FRotator RotationToAdd = FRotator(VerticalRotation.X, -MouseInput.X, -VerticalRotation.Y) * RotationSpeed * DeltaTime;
	AddActorWorldRotation(RotationToAdd);
}

void AInspectable::BeginPlay()
{
	Super::BeginPlay();

	InteractionWidget = Cast<UInteractionWidget>(DescriptiondWidget->GetWidget());
	InteractionWidget->SetText("");
}

void AInspectable::StartInspection()
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

	InitialLocation = GetActorLocation();
	InitialRotation = GetActorRotation();

	FVector CameraLocation = CameraManager->GetCameraLocation();
	CameraRotation = CameraManager->GetCameraRotation();

	FVector InspectLocation = CameraLocation + CameraRotation.RotateVector(FVector::ForwardVector) * DistanceFromCamera;

	SetActorLocation(InspectLocation);

	CameraRotation.Pitch = 0.0f;
	CameraRotation.Roll = 0.0f;
	IsInspected = true;
}

void AInspectable::EndInspection()
{
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	if (Controller == nullptr)
		return;

	AIntroductionUnrealCharacter* Character = Cast<AIntroductionUnrealCharacter>(Controller->GetCharacter());
	if (Character != nullptr)
		Character->bCanMove = true;

	SetActorLocation(InitialLocation);
	SetActorRotation(InitialRotation);

	IsInspected = false;
}

