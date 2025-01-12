// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ARPGHUD.generated.h"

class UAttributeMenuWidgetController;
struct FWidgetControllerParams;
class UOverlayWidgetController;
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


	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams);
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WidgetControllerParams);
	
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* Asc, UAttributeSet* Aset);
	
private:
	
	UPROPERTY()
	TObjectPtr<UARPGUserWidget> OverlayWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UARPGUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
};
