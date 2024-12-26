// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/ARPGWidgetController.h"

void UARPGWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComp = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UARPGWidgetController::BroadcastInitialValues()
{
	
}

void UARPGWidgetController::BindCallbacksDependencies()
{
}
