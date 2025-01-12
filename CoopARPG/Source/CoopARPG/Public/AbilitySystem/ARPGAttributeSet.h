// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "ARPGAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_DELEGATE_RetVal(FGameplayAttribute, FGetAttributeSignature);

USTRUCT(BlueprintType)
struct FEffectProperties
{
	GENERATED_BODY()
	
	FEffectProperties() {}
	
	FGameplayEffectContext ContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;
	UPROPERTY()
	AActor* SourceActor = nullptr;
	UPROPERTY()
	AController* SourceController = nullptr;
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;
	UPROPERTY()
	AActor* TargetActor = nullptr;
	UPROPERTY()
	AController* TargetController = nullptr;
	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

/**
 * 
 */
UCLASS()
class COOPARPG_API UARPGAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UARPGAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	//TMap<FGameplayTag, FGetAttributeSignature> TagsToAttributes;
	
	/*
	 * VITAL ATTRIBUTES
	 */

	/* --- VITAL: HEALTH ---- */
	UPROPERTY(ReplicatedUsing = OnRep_Health, BlueprintReadOnly, Category = "Base Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, Health);
	 
	UPROPERTY(ReplicatedUsing = OnRep_MaxHealth, BlueprintReadOnly, Category = "Base Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, MaxHealth);

	/* --- VITAL: MANA ---- */
	UPROPERTY(ReplicatedUsing = OnRep_Mana, BlueprintReadOnly, Category = "Base Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, Mana);
	
	UPROPERTY(ReplicatedUsing = OnRep_MaxMana, BlueprintReadOnly, Category = "Base Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, MaxMana);

	/*
	 * PRIMARY ATTRIBUTES
	 */

	/* --- PRIMARY: STRENGTH ---- */
	UPROPERTY(ReplicatedUsing = OnRep_Strength, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, Strength);

	/* --- PRIMARY: INTELLIGENCE ---- */
	UPROPERTY(ReplicatedUsing = OnRep_Intelligence, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, Intelligence);

	/* --- PRIMARY: RESILIENCE ---- */
	UPROPERTY(ReplicatedUsing = OnRep_Resilience, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, Resilience);

	/* --- PRIMARY: VIGOR ---- */
	UPROPERTY(ReplicatedUsing = OnRep_Vigor, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, Vigor);

	/* --- PRIMARY: DEXERTITY ---- */
	UPROPERTY(ReplicatedUsing = OnRep_Dexterity, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, Dexterity);

	/*
	 * SECONDARY ATTRIBUTES
	 */

	/* --- SECONDARY: Armor ---- */
	UPROPERTY(ReplicatedUsing = OnRep_Armor, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, Armor);

	/* --- SECONDARY: ArmorPenetration ---- */
	UPROPERTY(ReplicatedUsing = OnRep_ArmorPenetration, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, ArmorPenetration);

	/* --- SECONDARY: Block Chance ---- */
	UPROPERTY(ReplicatedUsing = OnRep_BlockChance, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, BlockChance);

	/* --- SECONDARY: CritialHitChance ---- */
	UPROPERTY(ReplicatedUsing = OnRep_CriticalHitChance, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, CriticalHitChance);
	
	/* --- SECONDARY: CriticalHitDamage ---- */
	UPROPERTY(ReplicatedUsing = OnRep_CriticalHitDamage, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, CriticalHitDamage);

	/* --- SECONDARY: CriticalHitResistance ---- */
	UPROPERTY(ReplicatedUsing = OnRep_CriticalHitResistance, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, CriticalHitResistance);

	/* --- SECONDARY: HealthRegeneration ---- */
	UPROPERTY(ReplicatedUsing = OnRep_HealthRegeneration, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, HealthRegeneration);

	/* --- SECONDARY: ManaRegeneration ---- */
	UPROPERTY(ReplicatedUsing = OnRep_ManaRegeneration, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, ManaRegeneration);
	

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;
	
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;
	
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;
	
	UFUNCTION()
	void OnRep_Dexterity(const FGameplayAttributeData& OldDexterity) const;

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;

	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;

	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;

	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;

	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;

	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;

	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;

	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;

private:

	void SetEffectProperties(const struct FGameplayEffectModCallbackData& Data, FEffectProperties& EffectProperties) const;
};


