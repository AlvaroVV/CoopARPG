// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGBlueprintFunctionLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "Player/ARPGPlayerState.h"
#include "UI/HUD/ARPGHUD.h"
#include "UI/WidgetController/ARPGWidgetController.h"

UOverlayWidgetController* UARPGBlueprintFunctionLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AARPGHUD* ARPGHud = Cast<AARPGHUD>(PC->GetHUD()))
		{
			AARPGPlayerState* PS = PC->GetPlayerState<AARPGPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams = FWidgetControllerParams(PC, PS, ASC, AS);
			return ARPGHud->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UARPGBlueprintFunctionLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AARPGHUD* ARPGHud = Cast<AARPGHUD>(PC->GetHUD()))
		{
			AARPGPlayerState* PS = PC->GetPlayerState<AARPGPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams = FWidgetControllerParams(PC, PS, ASC, AS);
			return ARPGHud->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}
