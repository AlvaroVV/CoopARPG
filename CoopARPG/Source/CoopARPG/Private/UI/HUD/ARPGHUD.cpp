// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/ARPGHUD.h"
#include "UI/Widget/ARPGUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"


UOverlayWidgetController* AARPGHUD::GetOverlayWidgetController(
	const FWidgetControllerParams& WidgetControllerParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WidgetControllerParams);
		OverlayWidgetController->BindCallbacksDependencies();
	}

	return OverlayWidgetController;
}

void AARPGHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* Asc, UAttributeSet* Aset)
{
	checkf(OverlayWidgetClass, TEXT ("Overlay widget class uninitialized"));
	checkf(OverlayWidgetControllerClass, TEXT ("OverlayController class uninitialized"));
	
	OverlayWidget = static_cast<UARPGUserWidget*>(CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass));

	const FWidgetControllerParams widgetControllerParams(PC, PS, Asc, Aset);
	UOverlayWidgetController* widgetController = GetOverlayWidgetController(widgetControllerParams);

	OverlayWidget->SetWidgetController(widgetController);
	widgetController->BroadcastInitialValues();
	
	OverlayWidget->AddToViewport();
}

