// Copyright Ratelbytes

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/AuraEnemyInterface.h"
#include "UI/WidgetController/AuraOverlayWidgetController.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "AuraEnemy.generated.h"

class UWidgetComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IAuraEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();

	/** Callback to Tag being added or removed. Fires as a result of FOnGameplayEffectTagCountChanged delegate */
	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
	
	// Enemy Interface
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	//~ Enemy Interface

	// Combat Interface
	virtual int32 GetPlayerLevel() override;
	virtual void Die() override;
	// ~ Combat Interface

	UPROPERTY(BlueprintReadOnly, Category="Combat")
	bool bHitReacting = false;

	UPROPERTY(BlueprintReadOnly, Category="Combat")
	float BaseWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	float LifeSpan = 5.f;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChangedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChangedDelegate;

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;

	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;
	
	/** Widget with Health Bar that that will be displayed above enemies */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
};
