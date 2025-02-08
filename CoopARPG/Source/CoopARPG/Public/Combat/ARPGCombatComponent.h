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

	virtual void OnRegister() override;
	virtual void OnComponentCreated() override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	
	FORCEINLINE int32 GetLevel() const{ return Level; };
	USkeletalMeshComponent* GetWeaponMesh() const { return Weapon; }
	FVector GetWeaponSocketLocation() const;
	
protected:

	UPROPERTY(EditAnywhere, ReplicatedUsing= OnRep_Level, Category = "ARPGCombat")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, Category = "ARPGCombat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
	
	UPROPERTY(EditAnywhere, Category = "ARPGCombat")
	FName WeaponSocketName;

	UFUNCTION()
	void OnRep_Level(int32 oldLevel);
};

