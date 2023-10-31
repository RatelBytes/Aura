// Copyright Ratelbytes

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AuraEnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAuraEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface, that is associated with Enemies and used to highlight them
 */
class AURA_API IAuraEnemyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/* Highlights an actor that implements IAuraEnemyInterface interface.*/
	virtual void HighlightActor() = 0;

	/* Clears highlight from an actor that implements IAuraEnemyInterface interface.*/
	virtual void UnHighlightActor() = 0;
};
