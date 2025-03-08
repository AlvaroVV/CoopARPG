// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UI/WidgetController/StatusBarWidgetController.h"
#include "ARPGCombatComponent.generated.h"

class UWidgetComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COOPARPG_API UARPGCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UARPGCombatComponent();
	
	virtual void OnComponentCreated() override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	
	FORCEINLINE int32 GetLevel() const{ return Level; };
	USkeletalMeshComponent* GetWeaponMesh() const { return Weapon; }
	FVector GetWeaponSocketLocation() const;

	void InitStatusBar(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* Asc, UAttributeSet* Aset);
	
	UStatusBarWidgetController* GetStatusBarWidgetController(const FWidgetControllerParams& WidgetControllerParams);
	
protected:

	UPROPERTY(EditAnywhere, ReplicatedUsing= OnRep_Level, Category = "ARPGCombat")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, Category = "ARPGCombat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
	
	UPROPERTY(EditAnywhere, Category = "ARPGCombat")
	FName WeaponSocketName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ARPGCombat")
	TObjectPtr<UWidgetComponent> StatusBarWidgetComp;

	UPROPERTY(EditAnywhere, Category = "ARPGCombat")
	TSubclassOf<UStatusBarWidgetController> StatusBarWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UStatusBarWidgetController> StatusBarWidgetController;

	UFUNCTION()
	void OnRep_Level(int32 oldLevel);
};

