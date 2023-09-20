// Copyright Ratelbytes


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot")));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

}

void AAuraEffectActor::ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	// Get the Ability System Component (ASC) from the target actor.
	const auto TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	if(!IsValid(TargetASC)) return;

	check(GameplayEffectClass);

	// The effect context is used to store additional data that might be relevant when applying the gameplay effect.
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	// This spec contains all the data needed to apply the gameplay effect, including the effect class, level, and context.
	FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);

	FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;

	// If the effect is infinite and should be removed on end overlap, it stores the active effect handle and the target's ASC in
	if(bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
	}
	
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	
	if(InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}

	// We apply it, and it removes itself
	if(DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}

	if(InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if(InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}

	// We apply it, and it removes itself
	if(DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}

	if(InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}

	if(InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if(!IsValid(TargetASC)) return;

		for (auto HandlePair = ActiveEffectHandles.CreateIterator(); HandlePair; ++HandlePair)
		{
			// Here we check if ASC of the actor is the same as the one stored in our Map (ActiveEffectHandles)
			if(TargetASC == HandlePair->Value)
			{
				// We remove the effect from the Target's ASC. In case of stacks, we remove just 1 effect from a stack.
				TargetASC->RemoveActiveGameplayEffect(HandlePair->Key, 1);
				HandlePair.RemoveCurrent();
			}
		}
	}
}
