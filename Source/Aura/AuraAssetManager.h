// Copyright Ratelbytes

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AuraAssetManager.generated.h"

/**
 * Singleton. Our own implementation of AssetManager.
 * For this to become default asset manager it should be specified in DefaultEngine.ini
 * AssetManagerClassName=/Script/Aura.AuraAssetManager should be added under [/Script/Engine.Engine] section
 */
UCLASS()
class AURA_API UAuraAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UAuraAssetManager& Get();

protected:
	/** Starts initial load, gets called from InitializeObjectReferences.
	 * Called very early, and this is where we start loading assets for the game */
	virtual void StartInitialLoading() override;
};
