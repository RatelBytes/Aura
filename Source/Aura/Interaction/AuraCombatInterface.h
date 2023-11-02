// Copyright Ratelbytes

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AuraCombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UAuraCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface, shared across all characters, including Enemies and Aura.
 * Utility functionality is put in this interface.
 */
class AURA_API IAuraCombatInterface
{
	GENERATED_BODY()

public:
	virtual int32 GetPlayerLevel();

	/** Returns the FVector (Location) of a socket on a weapon, so that we could spawn projectiles from this location */
	virtual FVector GetCombatSocketLocation();

	/** Function to update Facing direction for warping */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateFacingTarget(const FVector& Target);
};
