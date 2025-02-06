// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ARPGPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "BaseBehaviors/BehaviorTargetInterfaces.h"
#include "Input/ARPGInputComponent.h"
#include "Interaction/InteractableComponent.h"

AARPGPlayerController::AARPGPlayerController()
{
	bReplicates = true;
}

void AARPGPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(PlayerContext);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(PlayerContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	//Allows UI to respond to user input 
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AARPGPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CursorTrace();
}

void AARPGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UARPGInputComponent* ARPGInputComponent = CastChecked<UARPGInputComponent>(InputComponent);
	
	ARPGInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AARPGPlayerController::Move);
	ARPGInputComponent->BindAbilityActions(InputConfigData, this, &ThisClass::AbilityInputPressed, &ThisClass::AbilityInputReleased, &ThisClass::AbilityInputHeld);
}

void AARPGPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}


void AARPGPlayerController::AbilityInputPressed(FGameplayTag GameplayTag)
{
	//GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Red, *GameplayTag.ToString());
}

void AARPGPlayerController::AbilityInputReleased(FGameplayTag GameplayTag)
{
	//GEngine->AddOnScreenDebugMessage(2, 3.0f, FColor::Blue, *GameplayTag.ToString());
	if (GetARPGAbilitySystemComp() != nullptr)
		GetARPGAbilitySystemComp()->AbilityInputTagReleased(GameplayTag);
}

void AARPGPlayerController::AbilityInputHeld(FGameplayTag GameplayTag)
{
	//GEngine->AddOnScreenDebugMessage(3, 0.1f, FColor::Green, *GameplayTag.ToString());
	if (GetARPGAbilitySystemComp() != nullptr)
		GetARPGAbilitySystemComp()->AbilityInputTagHeld(GameplayTag);
}


void AARPGPlayerController::CursorTrace()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_GameTraceChannel1, false, Hit);
	if (!Hit.bBlockingHit)
		return;

	LastActorIntComp = CurrentActorIntComp;
	CurrentActorIntComp = Hit.GetActor()->FindComponentByClass<UInteractableComponent>();
	//Hit.GetActor()->GetComponentByClass(UInteractableComponent::StaticClass());
	
	if (LastActorIntComp != CurrentActorIntComp)
	{
		if (LastActorIntComp.Get()) LastActorIntComp->UnHighlightActor();
		if (CurrentActorIntComp.Get()) CurrentActorIntComp->HighlightActor();
	}
		
}

UARPGAbilitySystemComponent* AARPGPlayerController::GetARPGAbilitySystemComp()
{
	if (ARPGAbilitySystemComp == nullptr)
		ARPGAbilitySystemComp = Cast<UARPGAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	return ARPGAbilitySystemComp;
}
