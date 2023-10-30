// Copyright Ratelbytes


#include "Input/AuraInputConfig.h"

/*const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	// [=] capture by Value. [&] capture by Reference
	const auto FoundAction = AbilityInputActions.FindByPredicate([&](const FAuraInputAction& Action)
	{
		return Action.InputTag == InputTag;
	});

	if(FoundAction)
	{
		return FoundAction->InputAction;
	}
	else if(bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s], on InputConfig [%s]"), *InputTag.ToString(), *GetNameSafe(this));
	}
	return nullptr;
}*/

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (auto& Action : AbilityInputActions)
	{
		if(Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}
	
	if(bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s], on InputConfig [%s]"), *InputTag.ToString(), *GetNameSafe(this));
	}
	return nullptr;
}
