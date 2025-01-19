// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AttributeSet.h"
#include "AbilitySystem/ARPGAttributeSet.h"
#include "AbilitySystem/Data/ARPGAttributesInfoData.h"
#include "ARPGGameplayTags.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UARPGAttributeSet* AS = CastChecked<UARPGAttributeSet>(AttributeSet);

	if (AttributesInfoData)
	{
		for (FARPGAttributeInfo& attributeInfo : AttributesInfoData.Get()->AttributesInformation)
		{
			FARPGAttributeInfo newInfo = attributeInfo;
			newInfo.AttributeValue = attributeInfo.GameplayAttribute.GetNumericValue(AS);
			AttributeInfoDelegate.Broadcast(newInfo);
		}
	}
}

void UAttributeMenuWidgetController::BindCallbacksDependencies()
{
	UARPGAttributeSet* AS = CastChecked<UARPGAttributeSet>(AttributeSet);

	for (FARPGAttributeInfo& attributeInfo : AttributesInfoData.Get()->AttributesInformation)
	{
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(attributeInfo.GameplayAttribute).AddLambda
		(
			[this,attributeInfo](const FOnAttributeChangeData& data)
			{
				FARPGAttributeInfo newInfo = attributeInfo;
				newInfo.AttributeValue = data.NewValue;
				AttributeInfoDelegate.Broadcast(newInfo);
			}
		);
	}
}

