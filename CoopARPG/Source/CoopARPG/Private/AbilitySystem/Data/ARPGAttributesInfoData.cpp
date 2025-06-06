// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/ARPGAttributesInfoData.h"

#include "ARPGGameplayTags.h"

FARPGAttributeInfo UARPGAttributesInfoData::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound)
{
	for (FARPGAttributeInfo info : AttributesInformation )
	{
		if (info.AttributeTag == AttributeTag)
		{
			return info;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Attribute %s not found"), *AttributeTag.ToString());
	}
	
	return FARPGAttributeInfo();
}
