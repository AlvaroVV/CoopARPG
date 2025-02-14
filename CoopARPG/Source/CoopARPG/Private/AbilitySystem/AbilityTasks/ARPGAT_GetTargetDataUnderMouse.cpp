// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/ARPGAT_GetTargetDataUnderMouse.h"

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
		
	}
	
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult CursorHit;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	
	ValidData.Broadcast(CursorHit.Location);
}

void UARPGAT_GetTargetDataUnderMouse::SendMouseCursorData()
{
	
}
