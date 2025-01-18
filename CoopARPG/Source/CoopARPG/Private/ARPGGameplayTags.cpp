// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGGameplayTags.h"
#include "GameplayTagsManager.h"

FARPGGameplayTags FARPGGameplayTags::GameplayTags;

void FARPGGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get()
	.AddNativeGameplayTag(FName("Attributes.Primary.Strength"), FString("Increases Attack Power"));

	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Attributes.Primary.Vigor"), FString("Increases MaxHealth and HealthRegen"));

	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"), FString("Increases MaxMana and ManaRegen"));

	GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get()
			.AddNativeGameplayTag(FName("Attributes.Primary.Resilience"), FString("Increases Armor and Armor Penetration"));

	GameplayTags.Attributes_Primary_Dexterity = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Attributes.Primary.Dexterity"), FString("Increases chances of doing Critic and Block"));
	
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get()
	.AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("Reduces damage taken"));

	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get()
	.AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"), FString("Ignores percentage of Enemy Armor"));

	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get()
	.AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"), FString("Chance to cut damage in half"));

	GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get()
	.AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitChance"), FString("Chance to double damage plus critical hit bonus"));

	GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get()
	.AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitDamage"), FString("Bonus Damage added when critical"));
	
	GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get()
	.AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitResistance"), FString("Reduces critical hit damage of enemies"));

	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get()
	.AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"), FString("Amount of Health regenerated every 1 second"));
	
	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get()
	.AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"), FString("Amount of Mana regenerated every 1 second"));
	
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get()
	.AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"), FString("Maximum of Health"));

	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get()
	.AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"), FString("Maximum of Mana"));

	/*
	 * INPUT TAGS
	 */

	GameplayTags.InputTag_Action_Primary = UGameplayTagsManager::Get()
	.AddNativeGameplayTag(FName("Input.Action.Primary"), FString("Input tag for the Primary Action"));

	GameplayTags.InputTag_Action_Secondary = UGameplayTagsManager::Get()
	.AddNativeGameplayTag(FName("Input.Action.Secondary"), FString("Input tag for the Secondary Action"));

	GameplayTags.InputTag_Skill_1 = UGameplayTagsManager::Get()
	.AddNativeGameplayTag(FName("Input.Skill.1"), FString("Input tag for the Skill1 Action"));

	GameplayTags.InputTag_Skill_2 = UGameplayTagsManager::Get()
	.AddNativeGameplayTag(FName("Input.Skill.2"), FString("Input tag for the Skill2 Action"));

	GameplayTags.InputTag_Skill_3 = UGameplayTagsManager::Get()
	.AddNativeGameplayTag(FName("Input.Skill.3"), FString("Input tag for the Skill3 Action"));

	GameplayTags.InputTag_Skill_4 = UGameplayTagsManager::Get()
	.AddNativeGameplayTag(FName("Input.Skill.4"), FString("Input tag for the Skill4 Action"));
}
