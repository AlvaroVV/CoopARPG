// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/ARPGCharacterBase.h"
#include "Combat/ARPGCombatComponent.h"

// Sets default values
AARPGCharacterBase::AARPGCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	CombatComp = CreateDefaultSubobject<UARPGCombatComponent>(TEXT("CombatComponent"));
	CombatComp->SetIsReplicated(true);
}

UAbilitySystemComponent* AARPGCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

void AARPGCharacterBase::InitAbilityActorInfo()
{
}
