// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/ARPGCombatComponent.h"

#include "Character/ARPGCharacterBase.h"
#include "Components/WidgetComponent.h"
#include "Net/UnrealNetwork.h"
#include "UI/Widget/ARPGUserWidget.h"
#include "UI/WidgetController/StatusBarWidgetController.h"


// Sets default values for this component's properties
UARPGCombatComponent::UARPGCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	StatusBarWidgetComp = CreateDefaultSubobject<UWidgetComponent>("StatusBarWidget");
	
}

void UARPGCombatComponent::OnComponentCreated()
{
	Super::OnComponentCreated();

	AARPGCharacterBase* owner = Cast<AARPGCharacterBase>(GetOwner());
	if (owner)
	{
		Weapon->SetupAttachment(owner->GetMesh(), FName("WeaponHandSocket"));
		StatusBarWidgetComp->SetupAttachment(owner->GetRootComponent());
	}
}

FVector UARPGCombatComponent::GetWeaponSocketLocation() const
{
	return Weapon->GetSocketLocation(WeaponSocketName);
}

void UARPGCombatComponent::InitStatusBar(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* Asc,
	UAttributeSet* Aset)
{
	FWidgetControllerParams WidgetParams = FWidgetControllerParams(PC, PS, Asc, Aset);
	
	StatusBarWidgetController = GetStatusBarWidgetController(WidgetParams);
	
	UARPGUserWidget* UserWidget = Cast<UARPGUserWidget>(StatusBarWidgetComp->GetUserWidgetObject());
	
	if (UserWidget)
	{
		UserWidget->SetWidgetController(StatusBarWidgetController);
		StatusBarWidgetController->BroadcastInitialValues();
	}
}


UStatusBarWidgetController* UARPGCombatComponent::GetStatusBarWidgetController(const FWidgetControllerParams& WidgetControllerParams)
{
	if (StatusBarWidgetController == nullptr && StatusBarWidgetControllerClass != nullptr)
	{
		StatusBarWidgetController = NewObject<UStatusBarWidgetController>(this, StatusBarWidgetControllerClass);
		StatusBarWidgetController->SetWidgetControllerParams(WidgetControllerParams);
		StatusBarWidgetController->BindCallbacksDependencies();
	}
	return StatusBarWidgetController;
}

void UARPGCombatComponent::OnRep_Level(int32 oldLevel)
{
	
}



void UARPGCombatComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UARPGCombatComponent, Level);
}




