// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ARPGCharacter.h"

#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Player/ARPGPlayerController.h"
#include "Player/ARPGPlayerState.h"
#include "UI/HUD/ARPGHUD.h"


AARPGCharacter::AARPGCharacter()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 600.0f;
	SpringArmComp->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	SpringArmComp->bUsePawnControlRotation = false;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 10.0f;
	SpringArmComp->bInheritPitch = false;
	SpringArmComp->bInheritRoll = false;
	SpringArmComp->bInheritYaw = false;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComp->SetupAttachment(SpringArmComp,USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate.Yaw = 600.0f;
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AARPGCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//Only called on Server already.
	InitAbilityActorInfo();
	
}

void AARPGCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//Seems like it's only called on Clients already
	if (!HasAuthority())
	{
		InitAbilityActorInfo();
	}
}

void AARPGCharacter::InitAbilityActorInfo()
{
	AARPGPlayerState* ARPGPlayerState = GetPlayerState<AARPGPlayerState>();
	check(ARPGPlayerState);
	
	AbilitySystemComp = ARPGPlayerState->GetAbilitySystemComponent();
	AttributeSet = ARPGPlayerState->GetAttributeSet();
	
	AbilitySystemComp->InitAbilityActorInfo(ARPGPlayerState, this);
	Cast<UARPGAbilitySystemComponent>(AbilitySystemComp)->AbilityActorInfoSet();

	//Check local player as the other clients dont have access to other controllers or HUDs
	if (IsLocallyControlled())
	{
		AARPGPlayerController* playerController = Cast<AARPGPlayerController>(GetController());
		AARPGHUD* hud =  Cast<AARPGHUD>(playerController->GetHUD());
		hud->InitOverlay(playerController,ARPGPlayerState, AbilitySystemComp, AttributeSet);
	}
}

