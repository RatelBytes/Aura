// Copyright Ratelbytes

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "AuraPlayerController.generated.h"

class UDamageTextComponent;
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
	virtual void PlayerTick(float DeltaTime) override;

	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter, bool bBlockedHit, bool BCriticalHit);
	
protected:	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	/** Function that makes character automatically run to the clicked location using Spline*/
	void Autorun();
	void Move(const FInputActionValue& InputActionValue);

	void ShiftPressed() { bShiftKeyDown = true; }
	void ShiftReleased() { bShiftKeyDown = false; }
	bool bShiftKeyDown = false;
	
	/** Lazy loading and casting to ASC of our type */
	UAuraAbilitySystemComponent* GetASC();
	
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

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> ShiftAction;
	
	TWeakObjectPtr<APawn> CachedPawn = nullptr;

	IAuraEnemyInterface* LastActor = nullptr;
	IAuraEnemyInterface* ThisActor = nullptr;
	FHitResult CursorHit;

	
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

	/** Spline that we use for smooth movement of a character. We create it from NavPath.PathPoints*/
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;
	
};
