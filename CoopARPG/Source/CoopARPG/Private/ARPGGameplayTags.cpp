// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGGameplayTags.h"
#include "GameplayTagsManager.h"

FARPGGameplayTags FARPGGameplayTags::GameplayTags;

void FARPGGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get()
	.AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("Reduces damage taken"));
}
