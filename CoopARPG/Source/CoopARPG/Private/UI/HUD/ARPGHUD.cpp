// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/ARPGHUD.h"
#include "UI/Widget/ARPGUserWidget.h"
#include "UI/WidgetController/ARPGOverlayWidgetController.h"


UARPGOverlayWidgetController* AARPGHUD::GetOverlayWidgetController(
	const FWidgetControllerParams& WidgetControllerParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UARPGOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WidgetControllerParams);
	}

	return OverlayWidgetController;
}

void AARPGHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* Asc, UAttributeSet* Aset)
{
	checkf(OverlayWidgetClass, TEXT ("Overlay widget class uninitialized"));
	checkf(OverlayWidgetControllerClass, TEXT ("OverlayController class uninitialized"));
	
	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = static_cast<UARPGUserWidget*>(widget);

	const FWidgetControllerParams widgetControllerParams(PC, PS, Asc, Aset);
	UARPGOverlayWidgetController* widgetController = GetOverlayWidgetController(widgetControllerParams);

	OverlayWidget->SetWidgetController(widgetController);
	
	widget->AddToViewport();
}

