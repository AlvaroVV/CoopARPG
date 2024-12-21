// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ARPGCharacterBase.generated.h"

UCLASS(Abstract)
class COOPARPG_API AARPGCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	
	AARPGCharacterBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Combat)
	TObjectPtr<USkeletalMeshComponent> Weapon;

};
