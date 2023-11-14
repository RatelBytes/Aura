// Copyright Ratelbytes


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Interaction/AuraCombatInterface.h"

// Raw CPP struct to store data
struct AuraDamageStatics
{
	// Helper macros for declaring attribute captures 
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	
	AuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor,  Target, false);		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BlockChance,  Target, false);		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArmorPenetration,  Source, false);		
	}
};

static const AuraDamageStatics& DamageStatics()
{
	// Oldschool of creating object. No dynamics. It's static and always will be returned.
	static AuraDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	IAuraCombatInterface* SourceCombatInterface = Cast<IAuraCombatInterface>(SourceAvatar);
	IAuraCombatInterface* TargetCombatInterface = Cast<IAuraCombatInterface>(TargetAvatar);
	
	
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Get Damage Set by Caller Magnitude. This is damage we got from the GameplayAbility and its GE
	float Damage = Spec.GetSetByCallerMagnitude(FAuraGameplayTags::Get().Damage);


	// -------------------------------------
	// BlockChance halves the damage by 2
	// -------------------------------------

	// Capture BlockChance on Target, and etermine if there was a successful Block
	float TargetBlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluationParameters, TargetBlockChance);
	TargetBlockChance = FMath::Max<float>(TargetBlockChance, 0.f);

	// We check if our block chance proc. Let's say, block chance is 25%, then if RandRange() gives 27, it will not proc. 
	const bool bBlocked = FMath::RandRange(1, 100) < TargetBlockChance;

	// If Block, halve the damage (1/2 damage)
	Damage = bBlocked ? Damage / 2.f : Damage;


	
	// -------------------------------------
	// ArmorPenetration ignores a pecentatge of the Target's Armor.
	// -------------------------------------
	
	// Capture Target Armor and compare then compare it to ArmorPenetration
	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluationParameters, TargetArmor);
	TargetArmor = FMath::Max<float>(TargetArmor, 0.f);

	// Capture ArmorPenetration of the Source and compare it then to Target Armor
	float SourceArmorPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef, EvaluationParameters, SourceArmorPenetration);
	SourceArmorPenetration = FMath::Max<float>(SourceArmorPenetration, 0.f);

	// We get DataAsset containing lots of information about classes and coefficients
	const UCharacterClassInfo* CharacterClassInfo = UAuraAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);

	// That's a curve from CurveTable
	const FRealCurve* ArmorPenetrationCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("ArmorPenetration"), FString());

	// We get value from Curve using PlayerLevel as a parameter
	const float ArmorPenetrationCoefficient = ArmorPenetrationCurve->Eval(SourceCombatInterface->GetPlayerLevel());
			
	// ArmorPenetration ignores a percentage of the Target's Armor. Here we scale by ArmorPenetrationCoefficient. Meaning that N points in ArmorPenetration ignores 1% of Armor.
	const float EffectiveArmor = TargetArmor * (100 - SourceArmorPenetration * ArmorPenetrationCoefficient) / 100.f;

	const FRealCurve* EffectiveArmorCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveArmor"), FString());
	const float EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(TargetCombatInterface->GetPlayerLevel());
	
	// Armor ignores a percentage of incoming Damage
	Damage = Damage * ((100 - EffectiveArmor * EffectiveArmorCoefficient) / 100);
	

	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
	
}
