// Copyright Ratelbytes

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Use this function to assign a controller to a Widget */
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	
	/** A pointer to the controller, that this widget will be fetching/getting data from */
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:

	/** Is called when we bind/connect a Widget to its Controller. Basically, when WidgetController pointer is populated with an Object through SetWidgetController()  */
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
	
};
