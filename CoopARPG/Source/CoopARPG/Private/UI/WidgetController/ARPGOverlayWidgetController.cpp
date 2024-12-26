// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/ARPGOverlayWidgetController.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/ARPGAttributeSet.h"

void UARPGOverlayWidgetController::BroadcastInitialValues()
{
	//Super::BroadcastInitialValues();
	UARPGAttributeSet* ASet = CastChecked<UARPGAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(ASet->GetHealth());
	OnMaxHealthChanged.Broadcast(ASet->GetMaxHealth());
	OnManaChanged.Broadcast(ASet->GetMana());
	OnMaxManaChanged.Broadcast(ASet->GetMaxMana());
}

void UARPGOverlayWidgetController::BindCallbacksDependencies()
{
	//Super::BindCallbacksDependencies();
	UARPGAttributeSet* ASet = CastChecked<UARPGAttributeSet>(AttributeSet);
	AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(ASet->GetHealthAttribute())
	.AddUObject(this, &UARPGOverlayWidgetController::HealthChanged);
	
	AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(ASet->GetMaxHealthAttribute())
	.AddUObject(this, &UARPGOverlayWidgetController::MaxHealthChanged);

	AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(ASet->GetManaAttribute())
	.AddUObject(this, &UARPGOverlayWidgetController::ManaChanged);

	AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(ASet->GetMaxManaAttribute())
	.AddUObject(this, &UARPGOverlayWidgetController::MaxManaChanged);
	
}

void UARPGOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UARPGOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UARPGOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UARPGOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
