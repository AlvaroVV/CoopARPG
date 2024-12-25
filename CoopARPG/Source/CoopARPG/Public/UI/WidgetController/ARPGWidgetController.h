// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ARPGWidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
class APlayerState;
class APlayerController;

/**
 * 
 */
UCLASS()
class COOPARPG_API UARPGWidgetController : public UObject
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, Category= "WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category= "WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category= "WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComp;

	UPROPERTY(BlueprintReadOnly, Category= "WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;
 };
