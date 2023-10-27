// Copyright Ratelbytes


#include "UI/WidgetController/AuraAtributeMenuWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAuraAtributeMenuWidgetController::BindCallbacksToDependencies()
{
	
}

void UAuraAtributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfo);

	// We iterate through the TMap, that contains a list of GameplayTags and corresponding GameplayAttributes 
	for (auto& Pair : AS->TagsToAttributes)
	{
		FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);

		// We get FGameplayAttribute from our TMap through usage of FunctionPointer that we store as a Value.
		// We call the function stored in this FunctionPointer to get FGameplayAttribute, and then retrieve its numeric value.
		Info.AttributeValue = Pair.Value().GetNumericValue(AS);

		AttributeInfoDelegate.Broadcast(Info);
	}
}
