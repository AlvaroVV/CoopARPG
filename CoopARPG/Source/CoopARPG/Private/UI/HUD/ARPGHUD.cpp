// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/ARPGHUD.h"
#include "UI/Widget/ARPGUserWidget.h"


void AARPGHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	widget->AddToViewport();
}
