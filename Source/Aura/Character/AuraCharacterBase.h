// Copyright Ratelbytes

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/AuraCombatInterface.h"
#include "AuraCharacterBase.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public IAuraCombatInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:

	virtual void InitAbilityActorInfo();

	/** This function takes GameplayEffect and applies it to current GameplayAbilityComponent.
	 * Here it's used to initialized PrimaryAttributes and Secondary as well by providing BP with effect containing values for Attributes. */
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;

	/** Here we initialize Primary and Secondary Attributes with default values, that will be set when we start a game */
	void InitializeDefaultAttributes() const;

	/** Should work only on Server.
	 * Grants startup abilities. For that it accesses AbilitySystemComponent and calls its function to do so.  
	 */
	void AddCharacterAbilities();

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	/* Gameplay Effect that holds the default values for the PrimaryAttributes */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	/** Gameplay Effect that holds the values for the SecondaryAttributes.
	 * This is Infinite GameplayEffect, so whenever PrimaryAttribute changes, its derived SecondaryAttribute changes as well */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	/* Gameplay Effect that holds the default values for the VitalAttributes */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;


private:
	/** List of abilities that should be given from the beginning of a game */
	UPROPERTY(EditAnywhere, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	
};
