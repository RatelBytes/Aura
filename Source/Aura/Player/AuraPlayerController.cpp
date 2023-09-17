// Copyright Ratelbytes

#include "Player/AuraPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/AuraEnemyInterface.h"


AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	checkf(IsValid(AuraContext), TEXT("AAuraPlayerController::BeginPlay InputMappingContext is not set"));

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(IsValid(Subsystem), TEXT("AAuraPlayerController::BeginPlay. UEnhancedInputLocalPlayerSubsystem* Subsystem is not set"))

	Subsystem->AddMappingContext(AuraContext, 0);

	/* Mouse & Cursor Settings */
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

	
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CursorTrace();
	
}


void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FVector ForwardDirection = GetDirectionFromYaw(EAxis::X);
	const FVector RightDirection = GetDirectionFromYaw(EAxis::Y);

	// We use Lazy-loading for cached pawn
	if(!CachedPawn.IsValid())
	{
		CachedPawn = GetPawn<APawn>();
	}
	
	if (CachedPawn.IsValid())
	{
		if (!FMath::IsNearlyZero(InputAxisVector.Y, KINDA_SMALL_NUMBER))
		{
			CachedPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		}
		if (!FMath::IsNearlyZero(InputAxisVector.X, KINDA_SMALL_NUMBER))
		{
			CachedPawn->AddMovementInput(RightDirection, InputAxisVector.X);
		}
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	if(!CursorHit.bBlockingHit) return;

	// Last actor is what it was previous frame.
	LastActor = ThisActor;
	ThisActor = Cast<IAuraEnemyInterface>(CursorHit.GetActor());

	/*
	 *  Line Trace from cursor. There are several scenarios:
	 *  A. LastActor is null && ThisActor is null
	 *		- Do nothing
	 *	B. LastActor is null && ThisActor is valid
	 *		- Highlight ThisActor
	 *	C. LastActor is valid && ThisActor is null
	 *		- Unhighlight LastActor
	 *	D. Both actors are valid, but LastActor != ThisActor.
	 *		- UnHighlight LastActor, and Highlight ThisActor
	 *	E. Both actors are valid, and are the same actors
	 *		- Do nothing
	 */

	if(LastActor == nullptr)
	{
		if(ThisActor != nullptr)
		{
			// Case B
			ThisActor->HighlightActor();
		}
		else
		{
			// Case A. Both are null, do nothing.
		}
	}
	else // LastActor is valid
	{
		if(ThisActor == nullptr)
		{
			// Cast C. UnHighlight LastActor
			LastActor->UnHighlightActor();
		}
		else // both actors are valid
		{
			if(LastActor != ThisActor)
			{
				// Case D. Unhighlight LastActor
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				// Case E. Do nothing
			}
		}
	}
}

FVector AAuraPlayerController::GetDirectionFromYaw(EAxis::Type Axis)
{
	const FRotator ControllerRotation = GetControlRotation();

	// We take just the Yaw rotation of controller's rotation
	const FRotator YawRotation(0.f, ControllerRotation.Yaw, 0.f);

	// we take directions in unit vectors parallel to the floor
	return FRotationMatrix(YawRotation).GetUnitAxis(Axis);
}
