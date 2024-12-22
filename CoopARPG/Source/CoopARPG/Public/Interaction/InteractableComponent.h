// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"

UENUM(BlueprintType)
enum class EInteractableType : uint8
{
	Default = 0,
	Enemy = 250,
	Object = 251
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COOPARPG_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UInteractableComponent();

protected:

	UPROPERTY(BlueprintReadOnly);
	bool bIsHighlighted = false;

	UPROPERTY(EditAnywhere, Category = Interactable);
	EInteractableType InteractableType = EInteractableType::Default;

public:

	UFUNCTION(BlueprintCallable)
	void HighlightActor();
	
	UFUNCTION(BlueprintCallable)
	void UnHighlightActor();

	virtual void BeginPlay() override;

	void RegisterInteractableMesh(UMeshComponent* MeshComp);

private:

	UPROPERTY()
	TArray<TObjectPtr<UMeshComponent>> MeshComponents;
};
