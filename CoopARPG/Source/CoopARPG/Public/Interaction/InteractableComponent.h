// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COOPARPG_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UInteractableComponent();

protected:

	UPROPERTY(EditAnywhere, Category = Interactable);
	bool bIsHighlighted = false;
	

public:
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void HighlighActor();
	
	UFUNCTION(BlueprintCallable)
	void UnHighlighActor();
};
