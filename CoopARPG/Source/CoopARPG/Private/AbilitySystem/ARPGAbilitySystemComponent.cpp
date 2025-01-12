// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ARPGAbilitySystemComponent.h"


void UARPGAbilitySystemComponent::AbilityActorInfoSet()
{
	InitializeAttributes();
	InitializeGameplayAbilities();
	
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UARPGAbilitySystemComponent::EffectApplied);
}

void UARPGAbilitySystemComponent::InitializeAttributes()
{
	if (GetOwnerRole() != ROLE_Authority)
		return;
	
	for (const TSubclassOf<UGameplayEffect> GEClass : InitialAttributesValues)
	{
		FGameplayEffectContextHandle context =  MakeEffectContext();
		context.AddSourceObject(GetOwnerActor());
		const FGameplayEffectSpecHandle spec = MakeOutgoingSpec(GEClass, 1.0f, context);
		ApplyGameplayEffectSpecToSelf(*spec.Data.Get());
	}
}

void UARPGAbilitySystemComponent::InitializeGameplayAbilities()
{
	if (GetOwnerRole() != ROLE_Authority)
		return;
	
	for (TSubclassOf<UGameplayAbility> abilityClass : InitialGameplayAbilities)
	{
		FGameplayAbilitySpec abilitySpec = FGameplayAbilitySpec(abilityClass, 1);
		//GiveAbility(abilitySpec);
		GiveAbilityAndActivateOnce(abilitySpec);
	}
}

void UARPGAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& Spec,
                                                FActiveGameplayEffectHandle ActiveGameplayEffectHandle) const
{
	FGameplayTagContainer Tags;
	Spec.GetAllAssetTags(Tags);

	OnEffectAssetTags.Broadcast(Tags);
}
