// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GasSaveGame.h"

#include "AbilitySystemComponent.h"

bool UGasSaveGame::SaveGas(UAbilitySystemComponent* Asc, TArray<FGameplayAttribute> AttributesToSave,
                           FGameplayEffectQuery EffectQuery)
{
	if (!Asc)
	{
		return false;
	}
	
	for (const auto Attribute : AttributesToSave)
	{
		bool bSuccess;
		const auto Value = Asc->GetGameplayAttributeValue(Attribute, bSuccess);
		if (bSuccess)
		{
			AttributeSaveDatas.Add(Attribute, Value);
		}
	}
	
	if (EffectQuery.IsEmpty())
	{
		return true;
	}
	
	const auto ActiveEffects = Asc->GetActiveGameplayEffects();
	const auto ActiveEffectsToSave = ActiveEffects.GetActiveEffects(EffectQuery);
	for (const auto& Effect : ActiveEffectsToSave)
	{
		if (Effect.IsValid())
		{
			if (const auto Ptr = ActiveEffects.GetActiveGameplayEffect(Effect))
			{
				const auto RemainTime = Ptr->GetTimeRemaining(Asc->GetWorld()->GetTimeSeconds());
				const auto Spec = Ptr->Spec;
				FGameplayEffectSaveData NewSaveData;
				NewSaveData.InitFromSpec(Spec, RemainTime);
				GameplayEffectSaveDatas.Add(NewSaveData);
			}
		}
	}

	return true;
}

bool UGasSaveGame::LoadGas(UAbilitySystemComponent* Asc)
{
	if (!Asc)
	{
		return false;
	}

	for (const auto Attribute : AttributeSaveDatas)
	{
		Asc->SetNumericAttributeBase(Attribute.Key, Attribute.Value);
	}

	for (const auto Effect : GameplayEffectSaveDatas)
	{
		const auto Spec = Effect.MakeSpec();
		Asc->ApplyGameplayEffectSpecToSelf(Spec);
	}

	return true;
}
