// Copyright Ratelbytes

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

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
	
protected:
	/** Is called whenever effect is applied to this ASC */
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
