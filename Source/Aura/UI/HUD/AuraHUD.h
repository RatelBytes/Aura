// Copyright Ratelbytes

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AuraHUD.generated.h"

class UAuraAtributeMenuWidgetController;
class UAttributeSet;
class UAbilitySystemComponent;
struct FWidgetControllerParams;
class UAuraOverlayWidgetController;
class UAuraUserWidget;
/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:
	/** Getter with Lazy-loading, that creates and initializes OverlayWidgetController with parameters */
	UAuraOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	// Creates OverlayWidget and OverlayWidgetController, then ads them to viewport
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);


	
	/** Getter with Lazy-loading, that creates and initializes AttributeMenuWidgetController with parameters */
	UAuraAtributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);

protected:
	
private:

	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;
		
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UAuraOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraOverlayWidgetController> OverlayWidgetControllerClass;


	UPROPERTY()
	TObjectPtr<UAuraAtributeMenuWidgetController> AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraAtributeMenuWidgetController> AttributeMenuWidgetControllerClass;
};
