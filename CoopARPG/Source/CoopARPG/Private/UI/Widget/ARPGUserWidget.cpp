// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/ARPGUserWidget.h"

void UARPGUserWidget::SetWidgetController(UObject* NewWidgetController)
{
	WidgetController = NewWidgetController;
	OnWidgetControllerSet();
}
