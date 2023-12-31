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

	/** Return AnimMontage used for animating hit reaction. Implemented in C++ and then can be overriden in Blueprints  */
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;

	/** We call this only on server */
	virtual void Die() override;

	/** This multicast RPC handles what happens on all clients, when character dies*/
	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath();
	
protected:

	virtual void InitAbilityActorInfo();

	/** This function takes GameplayEffect and applies it to current GameplayAbilityComponent.
	 * Here it's used to initialized PrimaryAttributes and Secondary as well by providing BP with effect containing values for Attributes. */
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;

	/** Here we initialize Primary, Secondary and Vital Attributes with default values, that will be set when we start a game */
	virtual void InitializeDefaultAttributes() const;

	/** Should work only on Server.
	 * Grants startup abilities. For that it accesses AbilitySystemComponent and calls its function to do so.  
	 */
	void AddCharacterAbilities();


	/** Overriden function from IAuraCombatInterface that return location of the socket found on a weapon. For it to work WeaponTipSocketName should be set in Blueprint */
	virtual FVector GetCombatSocketLocation() override;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	/** Name of the socket, that SHOULD BE SET in Blueprint and that corresponds to the socket at the very tip of a weapon. It's where projectiles will be spawned */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	FName WeaponTipSocketName;
	
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

	
	// DISSOLVE EFFECTS

	/** Swaps materials and sets the dissolvable one */
	void Dissolve();

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UFUNCTION(BlueprintImplementableEvent)
	void StartWeaponDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> DissolveMaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterialInstance;
	
	
private:
	/** List of abilities that should be given from the beginning of a game */
	UPROPERTY(EditAnywhere, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;
	
};
