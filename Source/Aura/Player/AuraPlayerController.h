// Copyright Ratelbytes

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "AuraPlayerController.generated.h"

class USplineComponent;
class UAuraAbilitySystemComponent;
class UAuraInputConfig;
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

	/** Lazy loading and casting to ASC of our type */
	UAuraAbilitySystemComponent* GetASC();
	
	void Move(const FInputActionValue& InputActionValue);

	/** Function that is called, when a key defined in InputConfig is pressed. In our case it's LMB, RMB, 1,2,3,4 */
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	
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

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;


	// ---------------
	// Click-to-Move
	// ---------------
	
	FVector CachedDestination = FVector::ZeroVector;;

	/** Amount of time we've been following cursor*/
	float FollowTime = 0.f;
	float ShortPressThreshold = 0.5f;
	bool bAutoRunning = false;
	bool bTargeting = false;

	/** How close we should be to destination before we disable AutoRun */
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;
	
};
