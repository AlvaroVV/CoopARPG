// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ARPGCombatComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COOPARPG_API UARPGCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UARPGCombatComponent();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	FORCEINLINE int32 GetLevel() const{ return Level; };
	
protected:

	UPROPERTY(EditAnywhere, ReplicatedUsing= OnRep_Level, Category = "Combat")
	int32 Level = 1;

	UFUNCTION()
	void OnRep_Level(int32 oldLevel);
};
