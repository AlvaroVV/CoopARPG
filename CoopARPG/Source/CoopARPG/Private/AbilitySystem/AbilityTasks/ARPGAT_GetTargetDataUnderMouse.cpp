// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/ARPGAT_GetTargetDataUnderMouse.h"

#include "AbilitySystemComponent.h"

UARPGAT_GetTargetDataUnderMouse* UARPGAT_GetTargetDataUnderMouse::CreateGetTargetDataUnderMouse(
	UGameplayAbility* OwningAbility)
{
	UARPGAT_GetTargetDataUnderMouse* MyObj = NewAbilityTask<UARPGAT_GetTargetDataUnderMouse>(OwningAbility);
	
	return MyObj;
}

void UARPGAT_GetTargetDataUnderMouse::Activate()
{
	//It just prints some logs
	//Super::Activate();
	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();

	if (bIsLocallyControlled)
	{
		SendMouseCursorData();
	}
	else
	{
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
		
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey)
		.AddUObject(this, &UARPGAT_GetTargetDataUnderMouse::OnTargetDataReplicatedCallback);
		
		//Maybe the callback was already sent before being added so
		const bool bCalledDelegate =  AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);
		if (!bCalledDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
	
}

void UARPGAT_GetTargetDataUnderMouse::SendMouseCursorData()
{

	FScopedPredictionWindow ScopedPredictionWindow(AbilitySystemComponent.Get());
	
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult CursorHit;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	//ValidData.Broadcast(CursorHit.Location);

	FGameplayAbilityTargetDataHandle DataHandle;
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult = CursorHit;
	DataHandle.Add(Data);

	FGameplayTag ApplicationTag;
	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		DataHandle,
		ApplicationTag,
		AbilitySystemComponent->ScopedPredictionKey);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}

void UARPGAT_GetTargetDataUnderMouse::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle,
	FGameplayTag ActivationTag)
{
	//Target Data has been received
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}
