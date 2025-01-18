// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGInputConfigData.h"
#include "EnhancedInputComponent.h"
#include "ARPGInputComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COOPARPG_API UARPGInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UARPGInputComponent();

	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UARPGInputConfigData* InputConfig, UserClass* Object,
		PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc );
	
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UARPGInputComponent::BindAbilityActions(const UARPGInputConfigData* InputConfig, UserClass* Object,
	PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check (InputConfig)
	
	for (const FARPGInputAction& action : InputConfig->AbilityInputActions)
	{
		if (action.InputAction && action.InputTag.IsValid())
		{
			if (PressedFunc)
				BindAction(action.InputAction, ETriggerEvent::Started, Object, PressedFunc, action.InputTag);
			if (ReleasedFunc)
				BindAction(action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, action.InputTag);
			if (HeldFunc)
				BindAction(action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, action.InputTag);
		}
	}
	
}
