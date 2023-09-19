// Copyright Ratelbytes

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AuraOverlayWidgetController.generated.h"

struct FOnAttributeChangeData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UAuraOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	/** Here we pass initial values from WidgetController to a UserWidget, that is bound to this controller  */
	virtual void BroadcastInitialValues() override;

	/** Here we bind our callback functions to the changes happening to AttributeSet. In our case to Health/Mana changed */
	virtual void BindCallbacksToDependencies() override;
	
	// BlueprintAssignable so that we can bind to it inside blueprints
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

protected:
	/** Callback to changes with Health */
	void HealthChanged(const FOnAttributeChangeData& Data) const;

	/** Callback to changes with MaxHealth */
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
};
