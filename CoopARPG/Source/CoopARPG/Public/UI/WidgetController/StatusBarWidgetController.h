// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGWidgetController.h"
#include "StatusBarWidgetController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatusBarAttributeChangeSignature, float, newValue);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class COOPARPG_API UStatusBarWidgetController : public UARPGWidgetController
{
	GENERATED_BODY()

public:

	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksDependencies() override;

	UPROPERTY(BlueprintAssignable)
	FOnStatusBarAttributeChangeSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnStatusBarAttributeChangeSignature OnMaxHealthChanged;
};
