// Copyright Ratelbytes

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AuraTargetDataUnderMouse.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataSignature, const FGameplayAbilityTargetDataHandle&, DataHandle);


/**
 * This AbilityTask is capable of finding the HitResult under the cursor and the provides ability with this data.
 */
UCLASS()
class AURA_API UAuraTargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category="Ability|Tasks", DisplayName="TargetDataUnderMouse", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"))
	static UAuraTargetDataUnderMouse* CreateAuraTargetDataUnderMouse(UGameplayAbility* OwningAbility);

	/** This becomes an execution pin on the node in blueprint. We use this delegate to broadcast Data (location under cursor) */
	UPROPERTY(BlueprintAssignable)
	FMouseTargetDataSignature ValidDataDelegate;

private:
	/** Called to trigger the actual task once the delegates have been set up
	 *	Note that the default implementation does nothing and you don't have to call it */
	virtual void Activate() override;

	/** We use this function if we're locally controlled. */
	void SendMouseCursorData();
};
