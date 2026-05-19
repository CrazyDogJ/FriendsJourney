// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GEEC_ApplyEffectToSource.h"

#include "AbilitySystemComponent.h"

void UGEEC_ApplyEffectToSource::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                       FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	if (RelevantAttributesToCapture.IsValidIndex(0))
	{
		const auto AttributeToCapture = RelevantAttributesToCapture[0];
		
		float CurrentValue = 0.0f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(AttributeToCapture, FAggregatorEvaluateParameters(), CurrentValue);

		if (const auto TargetASC = ExecutionParams.GetTargetAbilitySystemComponent())
		{
			if (const auto SourceASC = ExecutionParams.GetSourceAbilitySystemComponent())
			{
				bool Found;
				const auto ModifiedValue = TargetASC->GetGameplayAttributeValue(AttributeToCapture.AttributeToCapture, Found);
				TargetASC->BP_ApplyGameplayEffectToTarget(EffectClass, SourceASC, FMath::Abs(CurrentValue - ModifiedValue), FGameplayEffectContextHandle());
			}
		}
	}
}
