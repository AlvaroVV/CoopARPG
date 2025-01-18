// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "ARPGPlayerController.generated.h"

class UARPGInputConfigData;
class UInputMappingContext;
class UInputAction;
//class IInteractableInterface;
class UInteractableComponent;

struct FInputActionValue;


UCLASS()
class COOPARPG_API AARPGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AARPGPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> PlayerContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UARPGInputConfigData> InputConfigData;

	void Move(const FInputActionValue& InputActionValue);
	void AbilityInputPressed(FGameplayTag GameplayTag);
	void AbilityInputReleased(FGameplayTag GameplayTag);
	void AbilityInputHeld(FGameplayTag GameplayTag);
	
	void CursorTrace();

	TWeakObjectPtr<UInteractableComponent> LastActorIntComp;
	TWeakObjectPtr<UInteractableComponent> CurrentActorIntComp;
};
