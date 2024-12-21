// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ARPGEnemy.h"

#include "Interaction/InteractableComponent.h"


AARPGEnemy::AARPGEnemy()
{
	InteractableComp = CreateDefaultSubobject<UInteractableComponent>(TEXT("InteractableComp"));
}

