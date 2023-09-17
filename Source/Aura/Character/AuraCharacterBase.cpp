// Copyright Ratelbytes

#include "AuraCharacterBase.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}