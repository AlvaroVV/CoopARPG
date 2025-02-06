// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGGameplayAbilityBase.h"
#include "ARPGProjectileAbility.generated.h"

/**
 * 
 */
UCLASS()
class COOPARPG_API UARPGProjectileAbility : public UARPGGameplayAbilityBase
{
	GENERATED_BODY()

protected:
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
};
