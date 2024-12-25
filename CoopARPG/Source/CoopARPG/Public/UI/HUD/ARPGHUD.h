// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ARPGHUD.generated.h"

struct FWidgetControllerParams;
class UARPGOverlayWidgetController;
class UARPGUserWidget;
class UAbilitySystemComponent;
class UAttributeSet;

/**
 * 
 */
UCLASS()
class COOPARPG_API AARPGHUD : public AHUD
{
	GENERATED_BODY()

public:


	UARPGOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* Asc, UAttributeSet* Aset);
	
private:
	
	UPROPERTY()
	TObjectPtr<UARPGUserWidget> OverlayWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UARPGUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UARPGOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UARPGOverlayWidgetController> OverlayWidgetControllerClass;
};
