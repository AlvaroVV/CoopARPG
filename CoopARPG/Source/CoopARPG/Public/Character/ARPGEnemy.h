// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ARPGCharacterBase.h"
#include "Interaction/InteractableInterface.h"
#include "ARPGEnemy.generated.h"

class UInteractableComponent;



UCLASS()
class COOPARPG_API AARPGEnemy : public AARPGCharacterBase//, public IInteractableInterface
{
	GENERATED_BODY()

public:
	AARPGEnemy();

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UInteractableComponent> InteractableComp;
	
	
};
