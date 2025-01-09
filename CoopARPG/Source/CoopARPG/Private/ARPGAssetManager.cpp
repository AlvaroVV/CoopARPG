// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGAssetManager.h"

#include "ARPGGameplayTags.h"

UARPGAssetManager& UARPGAssetManager::Get()
{
	check(GEngine)
	UARPGAssetManager* AssetManager = Cast<UARPGAssetManager> (GEngine->AssetManager);
	return *AssetManager;
}

void UARPGAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	
	FARPGGameplayTags::Get().InitializeNativeGameplayTags();
}
