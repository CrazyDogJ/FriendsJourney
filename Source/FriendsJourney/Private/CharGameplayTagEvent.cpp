// Fill out your copyright notice in the Description page of Project Settings.


#include "CharGameplayTagEvent.h"
#include "GameplayTagContainer.h"

void UCharGameplayTagEvent::OnTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if (NewCount > 0)
	{
		OnGameplayTagAdded(CallbackTag);
	}
	else
	{
		OnGameplayTagRemoved(CallbackTag);
	}
}
