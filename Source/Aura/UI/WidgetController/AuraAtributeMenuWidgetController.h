// Copyright Ratelbytes

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AuraAtributeMenuWidgetController.generated.h"

/**
 * WidgetController for Attributes Menu
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UAuraAtributeMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BindCallbacksToDependencies() override;

	virtual void BroadcastInitialValues() override;
	
};
