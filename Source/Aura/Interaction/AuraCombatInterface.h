// Copyright Ratelbytes

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AuraCombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAuraCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API IAuraCombatInterface
{
	GENERATED_BODY()

public:
	virtual int32 GetPlayerLevel();
};
