// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

class UInteractableComponent;

// This class does not need to be modified.
UINTERFACE()
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COOPARPG_API IInteractableInterface
{
	GENERATED_BODY()

	// Sounds interesting just having an interface to return the component.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UInteractableComponent* GetInteractableComponent();
};
