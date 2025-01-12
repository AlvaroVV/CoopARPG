// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"

#include "ARPGAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COOPARPG_API UARPGAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AbilityActorInfoSet();

	FEffectAssetTags OnEffectAssetTags;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	TArray<TSubclassOf<UGameplayEffect>> InitialAttributesValues;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> InitialGameplayAbilities;
	
	void InitializeAttributes();
	void InitializeGameplayAbilities();
	
	void EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& Spec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle) const;
	
};
