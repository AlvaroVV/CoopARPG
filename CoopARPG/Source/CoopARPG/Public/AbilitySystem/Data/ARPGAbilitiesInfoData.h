// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "ARPGAbilitiesInfoData.generated.h"


class UGameplayAbility;

USTRUCT(BlueprintType)
struct FARPGAbilityInfoData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayAbility> AbilityClass = nullptr;

	UPROPERTY(EditDefaultsOnly)
	int32 AbilityLevel = 0;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputActionTag = FGameplayTag();
};

/**
 * 
 */
UCLASS()
class COOPARPG_API UARPGAbilitiesInfoData : public UDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FARPGAbilityInfoData> Abilities;

public:
	TArray<FARPGAbilityInfoData> GetAbilities() { return Abilities; }
	
};
