
#include "Interaction/InteractableComponent.h"

UInteractableComponent::UInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();

	RegisterInteractableMesh(GetOwner()->FindComponentByClass<UMeshComponent>());
	
}

void UInteractableComponent::RegisterInteractableMesh(UMeshComponent* MeshComp)
{
	if (MeshComp != nullptr)
	{
		MeshComp->SetCustomDepthStencilValue(static_cast<uint8>(InteractableType));
		MeshComponents.Add(MeshComp);
	}
}

void UInteractableComponent::HighlightActor()
{
	bIsHighlighted = true;
	for (UMeshComponent* MeshComp : MeshComponents)
		MeshComp->SetRenderCustomDepth(true);
}

void UInteractableComponent::UnHighlightActor()
{
	bIsHighlighted = false;
	for (UMeshComponent* MeshComp : MeshComponents)
		MeshComp->SetRenderCustomDepth(false);
}



