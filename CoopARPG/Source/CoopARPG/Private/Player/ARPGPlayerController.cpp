// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ARPGPlayerController.h"
#include "EnhancedInputSubsystems.h"
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
	GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Red, *GameplayTag.ToString());
}

void AARPGPlayerController::AbilityInputReleased(FGameplayTag GameplayTag)
{
	GEngine->AddOnScreenDebugMessage(2, 3.0f, FColor::Blue, *GameplayTag.ToString());
}

void AARPGPlayerController::AbilityInputHeld(FGameplayTag GameplayTag)
{
	GEngine->AddOnScreenDebugMessage(3, 0.1f, FColor::Green, *GameplayTag.ToString());
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
	
	
	//Different situations to check.
	if (!LastActorIntComp.IsValid())
	{
		if (CurrentActorIntComp.IsValid())
		{
			//Case B. LastActor is null and CurrentActor is valid.
			CurrentActorIntComp->HighlightActor();
		}
		else
		{
			//Case A. Both are null.
		}
	}
	else 
	{
		if (!CurrentActorIntComp.IsValid())
		{
			//Case C.LastActor is valid and CurrentActor is null.
			LastActorIntComp->UnHighlightActor();
		}
		else
		{
			// Case D. Different Actors
			if (CurrentActorIntComp != LastActorIntComp)
			{
				CurrentActorIntComp->HighlightActor();
				LastActorIntComp->UnHighlightActor();
			}
			else
			{
				//Case E. Both are same actor.
			}
		}
	}
		
}
