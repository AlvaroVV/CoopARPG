// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ARPGCharacterBase.h"
#include "ARPGCharacter.generated.h"

/**
 * 
 */
UCLASS()
class COOPARPG_API AARPGCharacter : public AARPGCharacterBase
{
	GENERATED_BODY()

public:
	AARPGCharacter();

protected:

	UPROPERTY(EditAnywhere, Category = Camera)
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(EditAnywhere, Category = Camera)
	TObjectPtr<UCameraComponent> CameraComp;
	
};
