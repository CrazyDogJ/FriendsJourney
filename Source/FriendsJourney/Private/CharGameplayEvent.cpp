// Fill out your copyright notice in the Description page of Project Settings.


#include "CharGameplayEvent.h"

#include "AbilitySystemComponent.h"

class UWorld* UCharGameplayEvent::GetWorld() const
{
	return GetOuter()->GetWorld();
}

UAbilitySystemComponent* UCharGameplayEvent::GetOuterAbilitySystem() const
{
	return Cast<UAbilitySystemComponent>(GetOuter());
}

AActor* UCharGameplayEvent::GetAvatarActor() const
{
	if (GetOuterAbilitySystem() == nullptr)
	{
		return nullptr;
	}
	
	return GetOuterAbilitySystem()->GetAvatarActor();
}
