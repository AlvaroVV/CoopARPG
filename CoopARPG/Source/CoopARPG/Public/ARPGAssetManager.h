// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "ARPGAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class COOPARPG_API UARPGAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UARPGAssetManager& Get();
	
protected:
	virtual void StartInitialLoading() override;
};
