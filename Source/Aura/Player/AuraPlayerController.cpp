// Copyright Ratelbytes

#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "Player/AuraPlayerController.h"

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

	/* Cursor Settings */
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

	
}
