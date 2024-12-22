// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ARPGCharacterBase.h"
#include "ARPGCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()
class COOPARPG_API AARPGCharacter : public AARPGCharacterBase
{
	GENERATED_BODY()

public:
	AARPGCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
protected:

	UPROPERTY(EditAnywhere, Category = Camera)
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(EditAnywhere, Category = Camera)
	TObjectPtr<UCameraComponent> CameraComp;

private:

	void InitAbilityActorInfo();

	
};
