// Copyright Ratelbytes


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AuraOverlayWidgetController.h"


UAuraOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (IsValid(OverlayWidgetController))
	{
		return OverlayWidgetController;
	}
	
	// This is how UObject is created
	OverlayWidgetController = NewObject<UAuraOverlayWidgetController>(this, OverlayWidgetControllerClass);
	OverlayWidgetController->SetWidgetControllerParams(WCParams);

	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("AAuraHUD::InitOverlay. Overlay Widget Class is not initialized, please fill out BP_AuraHUD") );
	checkf(OverlayWidgetControllerClass, TEXT("AAuraHUD::InitOverlay. Overlay Widget Controller Class is not initialized, please fill out BP_AuraHUD") );

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);

	// we initialize our struct using its constructor
	const FWidgetControllerParams WidgetControllerParams (PC, PS, ASC, AS);

	// Here we create and initialize AuraOverlayWidgetController through our Getter with Lazy-Loading.
	UAuraOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	// Here we bind our WidgetController to UserWidget itself
	OverlayWidget->SetWidgetController(WidgetController);

	WidgetController->BroadcastInitialValues();
	
	OverlayWidget->AddToViewport();
}
