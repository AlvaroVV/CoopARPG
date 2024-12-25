// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ARPGHUD.generated.h"

class UARPGUserWidget;
/**
 * 
 */
UCLASS()
class COOPARPG_API AARPGHUD : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<UARPGUserWidget> OverlayWidget;

protected:
	virtual void BeginPlay() override;
	
private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UARPGUserWidget> OverlayWidgetClass;
};
