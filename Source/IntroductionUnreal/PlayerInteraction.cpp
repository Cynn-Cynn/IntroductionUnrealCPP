#include "PlayerInteraction.h"

UPlayerInteraction::UPlayerInteraction()
{
	PrimaryComponentTick.bCanEverTick = true;

	DetectionRange = 0.0f;
	Camera = nullptr;
	InteractableActor = nullptr;
	Hud = nullptr;
}

void UPlayerInteraction::BeginPlay()
{
	Super::BeginPlay();

	Camera = GetOwner()->GetComponentByClass<UCameraComponent>();
	Hud = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
}

void UPlayerInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GetInteractableObject();
}

void UPlayerInteraction::UseInteractableActor()
{
	if (InteractableActor != nullptr)
		IInteractable::Execute_Interact(InteractableActor);
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

	//On effectue le line trace pour trouver un objet
	if (World->LineTraceSingleByChannel(OUT Hit, Start, End, Channel, TraceParams))
	{
		//On récupère l'actor
		AActor* HitActor = Hit.GetActor();
		//On vérifie si c'est un objet interactif
		//Si oui, on le stock
		//Si non, on reset la variable qui stock l'actor
		if (HitActor != nullptr && HitActor->Implements<UInteractable>())
			SetInteractableObject(HitActor);
		else
			SetInteractableObject(nullptr);
	}
	else
	{
		//Si le line trace ne touche rien on reset la variable qui stock l'actor
		SetInteractableObject(nullptr);
	}
}

void UPlayerInteraction::SetInteractableObject(AActor* Interactable)
{
	if (Interactable == InteractableActor)
		return;

	InteractableActor = Interactable;

	if (InteractableActor == nullptr)
		Hud->SetInteractionDescription("");
	else
		Hud->SetInteractionDescription(IInteractable::Execute_GetDescription(InteractableActor));
}
