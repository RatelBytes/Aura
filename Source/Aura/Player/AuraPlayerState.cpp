// Copyright Ratelbytes


#include "Player/AuraPlayerState.h"

AAuraPlayerState::AAuraPlayerState()
{
	// We increase this number, because normally PlayerState is updated NOT frequently, around 2 times per second.
	NetUpdateFrequency = 100.f;

	
}
