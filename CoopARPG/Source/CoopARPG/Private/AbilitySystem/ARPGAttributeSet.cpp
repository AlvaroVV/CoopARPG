// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ARPGAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UARPGAttributeSet::UARPGAttributeSet()
{
	InitHealth((50.0f));
	InitMaxHealth((100.0f));
	InitMana((10.0f));
	InitMaxMana((20.0f));
}

void UARPGAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// VITAL
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);

	//PRIMARY
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, Vigor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, Dexterity, COND_None, REPNOTIFY_Always);

	//SECONDARY
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UARPGAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);
	
}

void UARPGAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
		UE_LOG(LogTemp, Warning, TEXT("Health: %f"), GetHealth());
	}
	
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
		UE_LOG(LogTemp, Warning, TEXT("Mana: %f"), GetMana());
	}
}

void UARPGAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties EffectProperties;
	SetEffectProperties(Data, EffectProperties);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
	
	
}


void UARPGAttributeSet::SetEffectProperties(const struct FGameplayEffectModCallbackData& Data,
                                            FEffectProperties& EffectProperties) const
{
	
	FGameplayEffectContextHandle contextHandle = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* sourceASC = contextHandle.GetOriginalInstigatorAbilitySystemComponent();
	
	if (IsValid(sourceASC) && sourceASC->AbilityActorInfo.IsValid() && sourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		EffectProperties.SourceActor = sourceASC->AbilityActorInfo->AvatarActor.Get();
		EffectProperties.SourceController = sourceASC->AbilityActorInfo->PlayerController.Get();
		if (EffectProperties.SourceController == nullptr && EffectProperties.SourceActor != nullptr)
		{
			if (const APawn* sourcePawn = Cast<APawn>(EffectProperties.SourceActor))
			{
				EffectProperties.SourceController = sourcePawn->GetController();
			}
		}
		if (EffectProperties.SourceController != nullptr)
		{
			EffectProperties.SourceCharacter = Cast<ACharacter>(EffectProperties.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		EffectProperties.TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		EffectProperties.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		EffectProperties.TargetCharacter= Cast<ACharacter>(EffectProperties.TargetActor);
		EffectProperties.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(EffectProperties.TargetActor); 
	}
}


/* ---- HEALTH ---- */
void UARPGAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, Health, OldHealth);
}

void UARPGAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, MaxHealth, OldMaxHealth);
}

/* ---- MANA---- */
void UARPGAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, Mana, OldMana);
}

void UARPGAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, MaxMana, OldMaxMana);
}

/* ---- STRENGTH---- */
void UARPGAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, Strength, OldStrength);
}

/* ---- INTELLIGENCE---- */
void UARPGAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, Intelligence, OldIntelligence);
}

/* ---- RESILIENCE---- */
void UARPGAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, Resilience, OldResilience);
}


/* ---- VIGOR---- */
void UARPGAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, Vigor, OldVigor);
}

/* ---- DEXERTITY ---- */
void UARPGAttributeSet::OnRep_Dexterity(const FGameplayAttributeData& OldDexterity) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, Dexterity, OldDexterity);
}

void UARPGAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, Armor, OldArmor);
}

void UARPGAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, ArmorPenetration, OldArmorPenetration);
}

void UARPGAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, BlockChance, OldBlockChance);
}

void UARPGAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, CriticalHitChance, OldCriticalHitChance);
}

void UARPGAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}

void UARPGAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, CriticalHitResistance, OldCriticalHitResistance);
}

void UARPGAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, HealthRegeneration, OldHealthRegeneration);
}

void UARPGAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UARPGAttributeSet, ManaRegeneration, OldManaRegeneration);
}

