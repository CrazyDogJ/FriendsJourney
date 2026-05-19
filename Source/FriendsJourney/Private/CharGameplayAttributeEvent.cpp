// Fill out your copyright notice in the Description page of Project Settings.


#include "CharGameplayAttributeEvent.h"

#include "GameplayEffectTypes.h"

void UCharGameplayAttributeEvent::AttributeChanged(const FOnAttributeChangeData& Data)
{
	K2_OnAttributeChanged(Data.Attribute, Data.OldValue, Data.NewValue);
}
