// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ARPGInputConfigData.h"

const UInputAction* UARPGInputConfigData::FindAbilitInputAction(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FARPGInputAction& ia : AbilityInputActions)
	{
		if (ia.InputAction && ia.InputTag == InputTag)
			return ia.InputAction;
	}

	if (bLogNotFound)
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s], on InputConfig [%s]"), *InputTag.ToString(), *GetNameSafe(this));

	return nullptr;
}
