// Copyright Ratelbytes


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
//#include "Blueprint/UserWidget.h"

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();

	// We create a widget and add to viewport. 
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}
