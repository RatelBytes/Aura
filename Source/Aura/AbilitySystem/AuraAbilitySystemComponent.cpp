// Copyright Ratelbytes


#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AuraGameplayTags.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	// We bind to delegate, and EffectApplied() will be called in response to any effect applied to this ASC
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for(TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		// GiveAbility(AbilitySpec);

		// Here we add abilities and immediately activate them.
		GiveAbilityAndActivateOnce(AbilitySpec);
	}
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	// We fill it with tags that go along with this Effect
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	// Here we broadcast all applied tags to the WidgetController, so that we can display them in our View
	EffectAssetTagsDelegate.Broadcast(TagContainer);
	
}
