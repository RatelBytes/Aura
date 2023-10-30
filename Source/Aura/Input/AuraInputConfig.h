// Copyright Ratelbytes

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AuraInputConfig.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FAuraInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
	
};


/**
 * DataAsset for storing structs with UInputAction and FGameplayTag
 */
UCLASS()
class AURA_API UAuraInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	/** Returns an InputAction associated with a given Tag*/
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;

	/** An array of structs FAuraInputAction, that holds UInputAction and FGameplayTag */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAuraInputAction> AbilityInputActions;
	
};
