// Copyright Ratelbytes

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();
	/** Called when this Pawn is possessed. Only called on the server (or in standalone). */
	virtual void PossessedBy(AController* NewController) override;

	/** PlayerState Replication Notification Callback */
	virtual void OnRep_PlayerState() override;

	// Combat Interface
	virtual int32 GetPlayerLevel() override;
	// ~Combat Interface 

private:
	/** Here we initialise ASC & AS, as well as setting Owner & Avatar for ASC */
	virtual void InitAbilityActorInfo() override;
};
