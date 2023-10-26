// Copyright Ratelbytes

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemLibrary.generated.h"

class UAuraAtributeMenuWidgetController;
class UAuraOverlayWidgetController;
/**
 * BlueprintFunctionLibrary for easy access to objects and functions.
 * In our case, we want to quickly access WidgetControllers, for example.
 */
UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|WidgetController")
	static UAuraOverlayWidgetController* GetAuraOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|WidgetController")
	static UAuraAtributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);
};
