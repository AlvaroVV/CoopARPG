// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/ARPGCharacterBase.h"

// Sets default values
AARPGCharacterBase::AARPGCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AARPGCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

// Called when the game starts or when spawned
void AARPGCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}


void AARPGCharacterBase::InitAbilityActorInfo()
{
}
