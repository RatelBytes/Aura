// Copyright Ratelbytes

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "AuraInputConfig.h"
#include "AuraInputComponent.generated.h"

/**
 * Overriden version of EnhancedInputComponent
 */
UCLASS()
class AURA_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	/**
	 * The function is a template function. It allows you to pass any class type (UserClass) and different types of function pointers (PressedFuncType, ReleasedFuncType, HeldFuncType) to be invoked when certain actions are triggered.
	 * @tparam UserClass The type of the object to which the actions will be bound.
	 * @tparam PressedFuncType Type of the function to be called when the action starts.
	 * @tparam ReleasedFuncType Type of the function to be called when the action completes.
	 * @tparam HeldFuncType Type of the function to be called while the action is being held.
	 * @param InputConfig This is the configuration object that contains all the mapping information between actions and gameplay tags.
	 * @param Object A pointer to an object to which you want to bind the actions.
	 * @param PressedFunc A function to be called when the action starts.
	 * @param ReleasedFunc A function to be called when the action is completed.
	 * @param HeldFunc A function to be called while the action is being held.
	 */
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc,ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
	{
		check(InputConfig);

		for (auto& Action : InputConfig->AbilityInputActions)
		{
			if(Action.InputAction && Action.InputTag.IsValid())
			{
				if(PressedFunc)
				{
					/** This line binds the PressedFunc function to be called on the Object when the action defined by Action.InputAction is first triggered (started).
					 * It also associates the action with a gameplay tag defined by Action.InputTag.*/
					BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputTag);
				}

				if(ReleasedFunc)
				{
					BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
				}
				
				if(HeldFunc)
				{
					BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Action.InputTag);
				}
			}
		}		
	}
};
