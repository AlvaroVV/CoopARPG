// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "ARPGCharacterBase.generated.h"

class UARPGGameplayAbilityBase;
class UAbilitySystemComponent;
class UAttributeSet;
class UARPGCombatComponent;

UCLASS(Abstract)
class COOPARPG_API AARPGCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	
	AARPGCharacterBase();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const {return AttributeSet;} 
	
protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UARPGCombatComponent> CombatComp;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComp;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

private:
	virtual void InitAbilityActorInfo();
	

};
