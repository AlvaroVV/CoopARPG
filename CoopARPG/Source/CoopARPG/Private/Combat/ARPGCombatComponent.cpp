// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/ARPGCombatComponent.h"

#include "Character/ARPGCharacterBase.h"
#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
UARPGCombatComponent::UARPGCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UARPGCombatComponent::OnRegister()
{
	Super::OnRegister();
	
}

void UARPGCombatComponent::OnComponentCreated()
{
	Super::OnComponentCreated();

	AARPGCharacterBase* owner = Cast<AARPGCharacterBase>(GetOwner());
	if (owner)
	{
		Weapon->SetupAttachment(owner->GetMesh(), FName("WeaponHandSocket"));
	}
}

FVector UARPGCombatComponent::GetWeaponSocketLocation() const
{
	return Weapon->GetSocketLocation(WeaponSocketName);
}

void UARPGCombatComponent::OnRep_Level(int32 oldLevel)
{
	
}



void UARPGCombatComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UARPGCombatComponent, Level);
}




