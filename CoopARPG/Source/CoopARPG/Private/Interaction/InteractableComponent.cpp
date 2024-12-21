
#include "Interaction/InteractableComponent.h"


UInteractableComponent::UInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}



void UInteractableComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsHighlighted)
	{
		DrawDebugSphere(GetWorld(), GetOwner()->GetActorLocation(), 32.0f, 12, FColor::Red);
	}
}

void UInteractableComponent::HighlighActor()
{
	bIsHighlighted = true;
}

void UInteractableComponent::UnHighlighActor()
{
	bIsHighlighted = false;
}


