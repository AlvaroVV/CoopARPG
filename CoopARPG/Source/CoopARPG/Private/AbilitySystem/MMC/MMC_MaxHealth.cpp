// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MMC/MMC_MaxHealth.h"
#include "AbilitySystem/ARPGAttributeSet.h"
#include "Character/ARPGCharacter.h"
#include "Combat/ARPGCombatComponent.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	VigorDef.AttributeToCapture = UARPGAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//Gather tags from source and target
	const FGameplayTagContainer* sourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* targetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters evaluationParams;
	evaluationParams.SourceTags = sourceTags;
	evaluationParams.TargetTags = targetTags;

	float vigorMagnitude = 0.0f;
	GetCapturedAttributeMagnitude(VigorDef, Spec, evaluationParams, vigorMagnitude);
	vigorMagnitude = FMath::Max(vigorMagnitude, 0.0f);
	
	UARPGCombatComponent* combatComp = Cast<AActor>(Spec.GetContext().GetSourceObject())->FindComponentByClass<UARPGCombatComponent>();
	if (combatComp)
	{
		float charLevel = combatComp->GetLevel();
		return 80.0f + vigorMagnitude * 2.5f + charLevel * 10.0f;
	}

	return 0.0f;
	
}