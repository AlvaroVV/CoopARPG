// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "AbilitySystem/ARPGAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	//Super::BroadcastInitialValues();
	UARPGAttributeSet* ASet = CastChecked<UARPGAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(ASet->GetHealth());
	OnMaxHealthChanged.Broadcast(ASet->GetMaxHealth());
	OnManaChanged.Broadcast(ASet->GetMana());
	OnMaxManaChanged.Broadcast(ASet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksDependencies()
{
	//Super::BindCallbacksDependencies();
	UARPGAttributeSet* ASet = CastChecked<UARPGAttributeSet>(AttributeSet);
	AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(ASet->GetHealthAttribute())
	.AddLambda(
		[this](const FOnAttributeChangeData& Data){OnHealthChanged.Broadcast(Data.NewValue);}
	);
	
	AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(ASet->GetMaxHealthAttribute())
	.AddLambda(
		[this](const FOnAttributeChangeData& Data){OnMaxHealthChanged.Broadcast(Data.NewValue);}
	);

	AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(ASet->GetManaAttribute())
	.AddLambda(
		[this](const FOnAttributeChangeData& Data){OnManaChanged.Broadcast(Data.NewValue);}
	);

	AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(ASet->GetMaxManaAttribute())
	.AddLambda(
		[this](const FOnAttributeChangeData& Data){OnMaxManaChanged.Broadcast(Data.NewValue);}
	);
	
	Cast<UARPGAbilitySystemComponent>(AbilitySystemComp)->OnEffectAssetTags.AddUObject
	(this, &UOverlayWidgetController::OnEffectAssetTagsChanged);
	
}

void UOverlayWidgetController::OnEffectAssetTagsChanged(FGameplayTagContainer Tags) const
{
	for (FGameplayTag Tag : Tags)
	{
		if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Message"))))
		{
			const FUIMessageWidgetRow* row = GetDataTableRowByTag<FUIMessageWidgetRow>(MessageWidgetDataTable, Tag);
			if (row)
				MessageWidgetDelegate.Broadcast(*row);
		}
		
	}
}

template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(const UDataTable* DataTable, const FGameplayTag Tag) const
{
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}

