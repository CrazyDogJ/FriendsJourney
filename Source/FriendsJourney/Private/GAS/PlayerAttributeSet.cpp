// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/PlayerAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

void UPlayerAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	ATTRIBUTE_MAX_ADJUST(Attribute, NewValue, Stamina, MaxStamina)
	ATTRIBUTE_MAX_ADJUST(Attribute, NewValue, Oxygen, MaxOxygen)
	ATTRIBUTE_MAX_ADJUST(Attribute, NewValue, Gauge, MaxGauge)
}

void UPlayerAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	ATTRIBUTE_MAX_SET(Data, Stamina, MaxStamina)
	ATTRIBUTE_MAX_SET(Data, Oxygen, MaxOxygen)
	ATTRIBUTE_MAX_SET(Data, Gauge, MaxGauge)
}

void UPlayerAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Oxygen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxOxygen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Gauge, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxGauge, COND_None, REPNOTIFY_Always);
}
