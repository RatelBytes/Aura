// Copyright Ratelbytes

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class IAuraEnemyInterface;
class UInputMappingContext;
struct FInputActionValue;
class UInputAction;

UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();
	
protected:	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
	
private:
	void Move(const FInputActionValue& InputActionValue);

	/* Every frame we check what's under cursor */
	void CursorTrace();
	
	/* Get Right or Forward Vectors, parallel to floor for the controller */
	FVector GetDirectionFromYaw(EAxis::Type Axis);
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	TWeakObjectPtr<APawn> CachedPawn = nullptr;

	IAuraEnemyInterface* LastActor = nullptr;
	IAuraEnemyInterface* ThisActor = nullptr;
	
};
