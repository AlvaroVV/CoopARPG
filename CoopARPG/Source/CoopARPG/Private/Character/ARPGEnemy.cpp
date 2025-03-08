// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ARPGEnemy.h"

#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "AbilitySystem/ARPGAttributeSet.h"
#include "Combat/ARPGCombatComponent.h"
#include "Interaction/InteractableComponent.h"


AARPGEnemy::AARPGEnemy()
{
	InteractableComp = CreateDefaultSubobject<UInteractableComponent>(TEXT("InteractableComp"));

	AbilitySystemComp = CreateDefaultSubobject<UARPGAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComp->SetIsReplicated(true);
	AbilitySystemComp->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UARPGAttributeSet>(FName("AttributeSet"));
	
}

void AARPGEnemy::BeginPlay()
{
	Super::BeginPlay();
	InteractableComp->RegisterInteractableMesh(CombatComp->GetWeaponMesh());
	InitAbilityActorInfo();
}

void AARPGEnemy::InitAbilityActorInfo()
{
	AbilitySystemComp->InitAbilityActorInfo(this,this);
	Cast<UARPGAbilitySystemComponent>(AbilitySystemComp)->AbilityActorInfoSet();

	CombatComp->InitStatusBar(nullptr, nullptr, AbilitySystemComp, AttributeSet);

}

