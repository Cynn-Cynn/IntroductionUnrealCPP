#include "TopViewCharacter.h"

ATopViewCharacter::ATopViewCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Main Camera"));
	MainCamera->SetupAttachment(GetMesh());

	//GetCapsuleComponent();
	//GetCharacterMovement();

	MoveAction = nullptr;
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
}

void ATopViewCharacter::MoveInput(const FInputActionValue& Value)
{
	FVector2D Input = Value.Get<FVector2D>();

	AddMovementInput(GetActorForwardVector(), Input.Y);
	AddMovementInput(GetActorRightVector(), Input.X);
}
