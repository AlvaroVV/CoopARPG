// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ARPGWidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
class APlayerState;
class APlayerController;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	FWidgetControllerParams(){}
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* ASet)
	: PlayerController (PC), PlayerState (PS), AbilitySystemComponent (ASC), AttributeSet (ASet) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetControllerParams")
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetControllerParams")
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetControllerParams")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetControllerParams")
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
	
};

/**
 * 
 */
UCLASS()
class COOPARPG_API UARPGWidgetController : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "WidgetController")
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);
	virtual void BroadcastInitialValues();
	virtual void BindCallbacksDependencies();

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
