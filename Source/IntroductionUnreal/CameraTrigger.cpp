#include "CameraTrigger.h"

UCameraComponent* ACameraTrigger::ActiveCamera = nullptr;

ACameraTrigger::ACameraTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	bDefaultCamera = false;
	bFade = false;
	FadeDuration = 1.0f;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Root);
	Camera->SetActive(false);

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	Trigger->SetupAttachment(Root);
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ACameraTrigger::ChangeCamera);
}

void ACameraTrigger::BeginPlay()
{
	Super::BeginPlay();

	if (bDefaultCamera)
	{
		EnableCamera(Camera, true);

		APlayerController* Controller = GetWorld()->GetFirstPlayerController();
		if (Controller != nullptr)
			Controller->SetViewTarget(this);
	}
}

void ACameraTrigger::ChangeCamera(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACameraTrigger::ActiveCamera == nullptr)
		UE_LOG(LogTemp, Warning, TEXT("Null"));

	if (ACameraTrigger::ActiveCamera == Camera)
		return;

	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	if (Controller == nullptr)
		return;

	if (Cast<ATopViewCharacter>(Controller->GetCharacter()) != OtherActor)
		return;

	if (bFade)
	{
		TObjectPtr<APlayerCameraManager> CameraManager = Controller->PlayerCameraManager;
		if (CameraManager == nullptr)
			return;

		CameraManager->StartCameraFade(0.0f, 1.0f, FadeDuration, FLinearColor::Black, false, true);
		GetWorldTimerManager().SetTimer(CameraFade, this, &ACameraTrigger::ChangeCameraAfterFade, FadeDuration + 1.0f, false);
	}
	else
	{
		EnableCamera(ACameraTrigger::ActiveCamera, false);
		EnableCamera(Camera, true);
		Controller->SetViewTarget(this);
	}
}

void ACameraTrigger::ChangeCameraAfterFade()
{
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	if (Controller == nullptr)
		return;

	EnableCamera(ACameraTrigger::ActiveCamera, false);
	EnableCamera(Camera, true);
	Controller->SetViewTarget(this);

	TObjectPtr<APlayerCameraManager> CameraManager = Controller->PlayerCameraManager;
	if (CameraManager == nullptr)
		return;

	CameraManager->StartCameraFade(1.0f, 0.0f, FadeDuration, FLinearColor::Black, false, true);
}

void ACameraTrigger::EnableCamera(UCameraComponent* CameraComponent, bool bActivate)
{
	if (CameraComponent == nullptr)
		return;

	if (bActivate && !CameraComponent->IsActive())
	{
		CameraComponent->SetActive(true);
		ACameraTrigger::ActiveCamera = CameraComponent;
	}
	else if (!bActivate && CameraComponent->IsActive())
	{
		CameraComponent->SetActive(false);
		ACameraTrigger::ActiveCamera = nullptr;
	}
}


