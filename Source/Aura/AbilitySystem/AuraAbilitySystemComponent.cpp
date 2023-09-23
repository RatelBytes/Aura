// Copyright Ratelbytes


#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	// We bind to delegate, and EffectApplied() will be called in response to any effect applied to this ASC
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);

	
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	// We fill it with tags that go along with this Effect
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	// Here we broadcast all applied tags to the WidgetController, so that we can display them in our View
	EffectAssetTags.Broadcast(TagContainer);
	
}
