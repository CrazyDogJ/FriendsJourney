// Copyright Epic Games, Inc. All Rights Reserved.

#include "GAS/AbilityAsync_WaitAttributeChangedWithContext.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AbilityAsync_WaitAttributeChangedWithContext)

UAbilityAsync_WaitAttributeChangedWithContext* UAbilityAsync_WaitAttributeChangedWithContext::WaitForAttributeChanged(AActor* TargetActor, FGameplayAttribute Attribute, bool OnlyTriggerOnce)
{
	UAbilityAsync_WaitAttributeChangedWithContext* MyObj = NewObject<UAbilityAsync_WaitAttributeChangedWithContext>();
	MyObj->SetAbilityActor(TargetActor);
	MyObj->Attribute = Attribute;
	MyObj->OnlyTriggerOnce = OnlyTriggerOnce;
	return MyObj;
}

void UAbilityAsync_WaitAttributeChangedWithContext::Activate()
{
	Super::Activate();

	if (UAbilitySystemComponent* ASC = GetAbilitySystemComponent())
	{
		MyHandle = ASC->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(this, &ThisClass::OnAttributeChanged);
	}
	else
	{
		EndAction();
	}
}

void UAbilityAsync_WaitAttributeChangedWithContext::OnAttributeChanged(const FOnAttributeChangeData& ChangeData)
{
	if (ShouldBroadcastDelegates())
	{
		Changed.Broadcast(ChangeData.Attribute, ChangeData.NewValue, ChangeData.OldValue,
			ChangeData.GEModData ? ChangeData.GEModData->EffectSpec : FGameplayEffectSpec(),
			ChangeData.GEModData ? ChangeData.GEModData->EvaluatedData : FGameplayModifierEvaluatedData());

		if (OnlyTriggerOnce)
		{
			EndAction();
		}
	}
	else
	{
		EndAction();
	}
}

void UAbilityAsync_WaitAttributeChangedWithContext::EndAction()
{
	if (UAbilitySystemComponent* ASC = GetAbilitySystemComponent())
	{
		ASC->GetGameplayAttributeValueChangeDelegate(Attribute).Remove(MyHandle);
	}
	Super::EndAction();
}

