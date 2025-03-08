// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/ARPGCharacterBase.h"
#include "Combat/ARPGCombatComponent.h"
#include "Components/CapsuleComponent.h"
#include "CoopARPG/CoopARPG.h"

// Sets default values
AARPGCharacterBase::AARPGCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);
		
	CombatComp = CreateDefaultSubobject<UARPGCombatComponent>(TEXT("CombatComponent"));
	CombatComp->SetIsReplicated(true);

	MotionWarpingComp = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
	MotionWarpingComp->SetIsReplicated(true);
}

UAbilitySystemComponent* AARPGCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

void AARPGCharacterBase::SetMotionWarpingTargetLocation(FName WarpTargetName, const FVector& NewTargetLocation)
{
	MotionWarpingComp->AddOrUpdateWarpTargetFromLocation(WarpTargetName,NewTargetLocation);
}

void AARPGCharacterBase::InitAbilityActorInfo()
{
}
