// Copyright Ratelbytes

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTagsSignature, const FGameplayTagContainer& /* AssetTags */)


/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	/** This function is called when we have already set AbilityActorInfo. It's a callback for us to proceed with the rest of setup of ASC, like binding to delegates */
	void AbilityActorInfoSet();

	/** This function is called to add/grant startup abilities */
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);

	/** We call this function from PlayerController as a result of pressing a key, that's bound to AbilityInput and we also pass the associated Tag into this function */
	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	
	// Delegate that broadcasts Tags that are coming with applied Effect
	FEffectAssetTagsSignature EffectAssetTagsDelegate;
	
protected:
	/** Is called whenever effect is applied to this ASC */
	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
