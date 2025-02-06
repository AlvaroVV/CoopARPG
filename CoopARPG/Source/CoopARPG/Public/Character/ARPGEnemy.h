// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ARPGCharacterBase.h"
#include "Interaction/InteractableInterface.h"
#include "ARPGEnemy.generated.h"

class UARPGCombatComponent;
class UInteractableComponent;



UCLASS()
class COOPARPG_API AARPGEnemy : public AARPGCharacterBase
{
	GENERATED_BODY()

public:
	AARPGEnemy();
	
	virtual void BeginPlay() override;
	
protected:
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UInteractableComponent> InteractableComp;

	virtual void InitAbilityActorInfo() override;
	
};
