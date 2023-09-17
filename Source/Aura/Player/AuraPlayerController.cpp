// Copyright Ratelbytes

#include "Player/AuraPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


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
			CachedPawn->AddMovementInput(ForwardDirection, InputAxisVector.X);
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