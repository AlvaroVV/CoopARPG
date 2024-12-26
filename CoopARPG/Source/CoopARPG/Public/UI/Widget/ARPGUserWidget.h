// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ARPGUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class COOPARPG_API UARPGUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly, Category = "ARPG User Widget")
	TObjectPtr<UObject> WidgetController;

	UFUNCTION(BlueprintCallable, Category = "ARPG User Widget")
	void SetWidgetController(UObject* NewWidgetController);

protected:
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetControllerSet();
};
