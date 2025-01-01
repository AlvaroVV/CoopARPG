// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MMC/MMC_MaxMana.h"

#include "AbilitySystem/ARPGAttributeSet.h"
#include "Combat/CombatComponent.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligenceDef.AttributeToCapture = UARPGAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//Gather tags from source and target
	const FGameplayTagContainer* sourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* targetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters evaluationParams;
	evaluationParams.SourceTags = sourceTags;
	evaluationParams.TargetTags = targetTags;

	float intelligenceMagnitude = 0.0f;
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, evaluationParams, intelligenceMagnitude);
	intelligenceMagnitude = FMath::Max(intelligenceMagnitude, 0.0f);
	
	UCombatComponent* combatComp = Cast<AActor>(Spec.GetContext().GetSourceObject())->FindComponentByClass<UCombatComponent>();
	if (combatComp)
	{
		float charLevel = combatComp->GetLevel();
		return 40.0f + intelligenceMagnitude * 2.5f + charLevel * 10.0f;
	}

	return 0.0f;
}
