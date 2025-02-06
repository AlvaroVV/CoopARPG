// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/ARPGCombatComponent.h"

#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
UARPGCombatComponent::UARPGCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

void UARPGCombatComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UARPGCombatComponent, Level);
}

void UARPGCombatComponent::OnRep_Level(int32 oldLevel)
{
	
}



