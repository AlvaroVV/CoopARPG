﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ARPGPlayerState.h"

#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "AbilitySystem/ARPGAttributeSet.h"
#include "Combat/CombatComponent.h"
#include "Net/UnrealNetwork.h"

AARPGPlayerState::AARPGPlayerState()
{
	AbilitySystemComp = CreateDefaultSubobject<UARPGAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComp->SetIsReplicated(true);
	AbilitySystemComp->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UARPGAttributeSet>(FName("AttributeSet"));

	CombatComp = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
	CombatComp->SetIsReplicated(true);
	
	SetNetUpdateFrequency(100.0f);
}

UAbilitySystemComponent* AARPGPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

