// Copyright Ratelbytes

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "AuraMMC_MaxMana.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraMMC_MaxMana : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UAuraMMC_MaxMana();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
	
private:
	/** This struct will hold captured attribute, in our case it's Intelligence */
	FGameplayEffectAttributeCaptureDefinition IntelligenceDef;
};
