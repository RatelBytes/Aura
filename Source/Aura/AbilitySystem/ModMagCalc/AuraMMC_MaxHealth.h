// Copyright Ratelbytes

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "AuraMMC_MaxHealth.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraMMC_MaxHealth : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UAuraMMC_MaxHealth();

	/** This function makes calculations and return the value for MaxHealth */
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	/** This struct will hold captured attribute, in our case it's Vigor */
	FGameplayEffectAttributeCaptureDefinition VigorDef;
};
