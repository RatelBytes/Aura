// Copyright Ratelbytes

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Data/CharacterClassInfo.h"
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

	/** This function sets Primary, Secondary and Vital Attributes for a character. CharacterClassInfo DataAsset should be present at GameMode for it to work. */
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|CharacterClassDefaults")
	static void InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC);
};
