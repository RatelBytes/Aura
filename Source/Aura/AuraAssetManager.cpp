// Copyright Ratelbytes


#include "AuraAssetManager.h"
#include "AuraGameplayTags.h"
#include "AbilitySystemGlobals.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine);

	// We access default AssetManager, set in config, and then cast it to our own type.
	UAuraAssetManager* AuraAssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);

	return *AuraAssetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FAuraGameplayTags::InitializeNativeGameplayTags();

	/** This should be called for every project that uses Target Data (part of AbilitySystem) */
	UAbilitySystemGlobals::Get().InitGlobalData();
}
