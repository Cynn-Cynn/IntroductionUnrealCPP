#include "TopViewCharacter.h"

ATopViewCharacter::ATopViewCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerInteraction = CreateDefaultSubobject<UPlayerInteraction>(TEXT("Player Interaction"));

	//MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Main Camera"));
	//MainCamera->SetupAttachment(GetMesh());

	//GetCapsuleComponent();
	//GetCharacterMovement();

	MoveAction = nullptr;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ATopViewCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATopViewCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATopViewCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInput == nullptr)
		return;

	EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATopViewCharacter::MoveInput);
	EnhancedInput->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ATopViewCharacter::InteractInput);
	//EnhancedInput->BindAction(MouseAction, ETriggerEvent::Triggered , this, &ATopViewCharacter::CameraInput);
}

void ATopViewCharacter::MoveInput(const FInputActionValue& Value)
{
	FVector2D Input = Value.Get<FVector2D>();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	TObjectPtr<APlayerCameraManager> CameraManager = PlayerController->PlayerCameraManager;
	if (CameraManager == nullptr)
		return;

	FRotator CameraRotation = CameraManager->GetCameraRotation();
	CameraRotation.Pitch = 0.0f;
	CameraRotation.Roll = 0.0f;

	AddMovementInput(CameraRotation.RotateVector(FVector::ForwardVector), Input.Y);
	AddMovementInput(CameraRotation.RotateVector(FVector::RightVector), Input.X);
}

void ATopViewCharacter::InteractInput(const FInputActionValue& _)
{
	PlayerInteraction->UseInteractableActor();
}

//void ATopViewCharacter::CameraInput(const FInputActionValue& Value)
//{
//	FVector2D Input = Value.Get<FVector2D>();
//
//	AddControllerYawInput(Input.X);
//	AddControllerPitchInput(Input.Y);
//}
