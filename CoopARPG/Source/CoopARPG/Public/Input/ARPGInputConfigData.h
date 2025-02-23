// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "ARPGInputConfigData.generated.h"


USTRUCT(BlueprintType)
struct FARPGInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();

	
};

/**
 * 
 */
UCLASS()
class COOPARPG_API UARPGInputConfigData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FARPGInputAction> AbilityInputActions;

	const UInputAction* FindAbilitInputAction(const FGameplayTag& InputTag, bool bLogNotFound = false) const;
};
