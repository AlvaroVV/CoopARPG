// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ARPGGameplayAbilityBase.h"
#include "Character/ARPGCharacterBase.h"

void UARPGGameplayAbilityBase::SetLocationWarping(FName WarpTargetName, const FVector& Location)
{
	AActor* Avatar = GetAvatarActorFromActorInfo();
	AARPGCharacterBase* AvatarCharacterBase = Cast<AARPGCharacterBase>(Avatar);
	
	if (AvatarCharacterBase)
	{
		AvatarCharacterBase->SetMotionWarpingTargetLocation(WarpTargetName, Location);
	}
}
