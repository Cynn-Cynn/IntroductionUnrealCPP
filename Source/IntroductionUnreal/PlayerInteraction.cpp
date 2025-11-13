#include "PlayerInteraction.h"

UPlayerInteraction::UPlayerInteraction()
{
	PrimaryComponentTick.bCanEverTick = true;

	DetectionRange = 0.0f;
	Camera = nullptr;
}

void UPlayerInteraction::BeginPlay()
{
	Super::BeginPlay();

	Camera = GetOwner()->GetComponentByClass<UCameraComponent>();
}

void UPlayerInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GetInteractableObject();
}

void UPlayerInteraction::GetInteractableObject()
{
	if (Camera == nullptr)
		return;

	UWorld* World = GetWorld();
	if (World == nullptr)
		return;

	//Resultat
	FHitResult Hit;
	//Points de départ et d'arrivée du line trace
	FVector Start = Camera->GetComponentLocation();
	FVector End = Start + Camera->GetForwardVector() * DetectionRange;
	//Channel sur lequel on effectue le line trace
	ECollisionChannel Channel(ECC_GameTraceChannel1);
	//Paramètres supplémentaires, le dernier permet d'ignorer un acteur dans le calcul
	const FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	if (World->LineTraceSingleByChannel(OUT Hit, Start, End, Channel, TraceParams))
	{
		AActor* InteractableActor = Hit.GetActor();
		if (InteractableActor != nullptr && InteractableActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
			IInteractable::Execute_Interact(InteractableActor);
	}
}
