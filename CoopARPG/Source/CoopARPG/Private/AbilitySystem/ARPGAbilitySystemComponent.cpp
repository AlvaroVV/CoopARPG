// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ARPGAbilitySystemComponent.h"

#include "AbilitySystem/Data/ARPGAbilitiesInfoData.h"


void UARPGAbilitySystemComponent::AbilityActorInfoSet()
{
	InitializeAttributes();
	InitializeGameplayAbilities();
	
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UARPGAbilitySystemComponent::ClientEffectApplied);
}

void UARPGAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& Tag)
{
	if (!Tag.IsValid())
		return;

	for (FGameplayAbilitySpec& Ability: GetActivatableAbilities())
	{
		if (Ability.GetDynamicSpecSourceTags().HasTagExact(Tag))
		{
			AbilitySpecInputPressed(Ability);
			if (!Ability.IsActive())
				TryActivateAbility(Ability.Handle);
		}
	}
}

void UARPGAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& Tag)
{
	if (!Tag.IsValid())
		return;

	for (FGameplayAbilitySpec& Ability: GetActivatableAbilities())
	{
		if (Ability.GetDynamicSpecSourceTags().HasTagExact(Tag))
		{
			AbilitySpecInputReleased(Ability);
			
		}
	}
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

	if (AbilitiesInfoData == nullptr)
		return;
	
	for (FARPGAbilityInfoData& abilityInfo : AbilitiesInfoData->GetAbilities())
	{
		FGameplayAbilitySpec abilitySpec = FGameplayAbilitySpec(abilityInfo.AbilityClass, abilityInfo.AbilityLevel);
		abilitySpec.GetDynamicSpecSourceTags().AddTag(abilityInfo.InputActionTag);
		GiveAbility(abilitySpec);
	}
}

void UARPGAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& Spec,
                                                FActiveGameplayEffectHandle ActiveGameplayEffectHandle) const
{
	FGameplayTagContainer Tags;
	Spec.GetAllAssetTags(Tags);

	OnEffectAssetTags.Broadcast(Tags);
}
