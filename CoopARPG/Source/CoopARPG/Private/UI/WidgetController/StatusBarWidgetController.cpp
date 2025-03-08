// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/StatusBarWidgetController.h"

#include "AbilitySystem/ARPGAttributeSet.h"

void UStatusBarWidgetController::BroadcastInitialValues()
{
	//Super::BroadcastInitialValues();
	UARPGAttributeSet* ASet = CastChecked<UARPGAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(ASet->GetHealth());
	OnMaxHealthChanged.Broadcast(ASet->GetMaxHealth());
	
}

void UStatusBarWidgetController::BindCallbacksDependencies()
{
	//Super::BindCallbacksDependencies();
	UARPGAttributeSet* ASet = CastChecked<UARPGAttributeSet>(AttributeSet);
	AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(ASet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(ASet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);
}
