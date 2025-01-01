// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ARPGAbilitySystemComponent.h"


void UARPGAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UARPGAbilitySystemComponent::EffectApplied);
	InitializeAttributes();
}

void UARPGAbilitySystemComponent::InitializeAttributes()
{
	for (const TSubclassOf<UGameplayEffect> GEClass : InitialAttributesValues)
	{
		const FGameplayEffectContextHandle context =  MakeEffectContext();
		const FGameplayEffectSpecHandle spec = MakeOutgoingSpec(GEClass, 1.0f, context);
		ApplyGameplayEffectSpecToSelf(*spec.Data.Get());
	}
}

void UARPGAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& Spec,
                                                FActiveGameplayEffectHandle ActiveGameplayEffectHandle) const
{
	FGameplayTagContainer Tags;
	Spec.GetAllAssetTags(Tags);

	OnEffectAssetTags.Broadcast(Tags);
}
