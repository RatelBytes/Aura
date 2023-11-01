// Copyright Ratelbytes


#include "AbilitySystem/Task/AuraTargetDataUnderMouse.h"
#include "AbilitySystemComponent.h"

UAuraTargetDataUnderMouse* UAuraTargetDataUnderMouse::CreateAuraTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UAuraTargetDataUnderMouse* MyObj = NewAbilityTask<UAuraTargetDataUnderMouse>(OwningAbility);
	return MyObj;
}

void UAuraTargetDataUnderMouse::Activate()
{
	if(const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled())
	{
		SendMouseCursorData();
	}
	else
	{
		//TODO: We are on the server, so listen for target data.
	}
	

}

void UAuraTargetDataUnderMouse::SendMouseCursorData()
{
	// This makes everything below in this function to be predicted
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());
	
	auto PlayerController = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult CursorHit;
	PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	FGameplayAbilityTargetDataHandle DataHandle;
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult = CursorHit;
	DataHandle.Add(Data);
	
	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		DataHandle,
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey);

	if(ShouldBroadcastAbilityTaskDelegates())
	{
		ValidDataDelegate.Broadcast(DataHandle);
	}
}
