// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "ARPGAT_GetTargetDataUnderMouse.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataDelegateSignature, const FGameplayAbilityTargetDataHandle&, DataHandle);

/**
 * 
 */
UCLASS()
class COOPARPG_API UARPGAT_GetTargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FMouseTargetDataDelegateSignature ValidData;

	UFUNCTION(BlueprintCallable, Category = "ARPGAbility|Tasks", meta = (DisplayName = "GetTargetDataUnderMouse",HidePin = "OwningAbility",
		DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"))
	static UARPGAT_GetTargetDataUnderMouse* CreateGetTargetDataUnderMouse(UGameplayAbility* OwningAbility);


private:

	virtual void Activate() override;
	void SendMouseCursorData();

	void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag);
};
