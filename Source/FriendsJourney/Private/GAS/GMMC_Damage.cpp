// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GMMC_Damage.h"

#include "GAS/BaseAttributeSet.h"
#include "Kismet/KismetMathLibrary.h"

namespace Damage
{
	UE_DEFINE_GAMEPLAY_TAG(BaseDamage, FName{TEXTVIEW("Damage.Base")})
	UE_DEFINE_GAMEPLAY_TAG(BaseDamageFloating, FName{TEXTVIEW("Data.Floating")})
	UE_DEFINE_GAMEPLAY_TAG(BaseCriticalRate, FName{TEXTVIEW("Data.CriticalRate")})
	UE_DEFINE_GAMEPLAY_TAG(BaseCriticalMultiplier, FName{TEXTVIEW("Data.CriticalMultiplier")})
	UE_DEFINE_GAMEPLAY_TAG(IsCritical, FName{TEXTVIEW("Damage.IsCritical")})
}

UGMMC_Damage::UGMMC_Damage()
{
	const auto DamageDef = FGameplayEffectAttributeCaptureDefinition(UBaseAttributeSet::GetDamageAttribute(),
		EGameplayEffectAttributeCaptureSource::Source, true);

	const auto CriticalProbability = FGameplayEffectAttributeCaptureDefinition(UBaseAttributeSet::GetCriticalProbabilityAttribute(),
		EGameplayEffectAttributeCaptureSource::Source, true);

	const auto CriticalMultiplier = FGameplayEffectAttributeCaptureDefinition(UBaseAttributeSet::GetCriticalMultiplierAttribute(),
		EGameplayEffectAttributeCaptureSource::Source, true);
	
	RelevantAttributesToCapture.Append({DamageDef, CriticalProbability, CriticalMultiplier});
}

float UGMMC_Damage::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	float Damage = 0.f;
	GetCapturedAttributeMagnitude(RelevantAttributesToCapture[0], Spec, FAggregatorEvaluateParameters(), Damage);
	
	float CriticalProbability = 0.f;
	GetCapturedAttributeMagnitude(RelevantAttributesToCapture[1], Spec, FAggregatorEvaluateParameters(), CriticalProbability);
 
	float CriticalMultiplier = 0.f;
	GetCapturedAttributeMagnitude(RelevantAttributesToCapture[2], Spec, FAggregatorEvaluateParameters(), CriticalMultiplier);

	Damage += Spec.GetSetByCallerMagnitude(Damage::BaseDamage);
	const auto DamageFloating = Spec.GetSetByCallerMagnitude(Damage::BaseDamageFloating);
	CriticalProbability += Spec.GetSetByCallerMagnitude(Damage::BaseCriticalRate);
	CriticalMultiplier += Spec.GetSetByCallerMagnitude(Damage::BaseCriticalMultiplier);
	
	float HealthMod = UKismetMathLibrary::RandomIntegerInRange(FMath::Max(0, Damage - DamageFloating), Damage + DamageFloating);

	if (FMath::FRand() < (CriticalProbability / 100.f))
	{
		HealthMod *= CriticalMultiplier; // 假设2倍暴击伤害
		
		FGameplayEffectSpec* MutableSpec = const_cast<FGameplayEffectSpec*>(&Spec);
		MutableSpec->AppendDynamicAssetTags(FGameplayTagContainer(Damage::IsCritical));
	}

	if (const auto Hit = Spec.GetEffectContext().GetHitResult())
	{
		if (const auto HitBoxPM = Cast<UHitBoxPhysicalMaterial>(Hit->PhysMaterial))
		{
			HealthMod *= HitBoxPM->DamageMultiplier;
		}
	}

	HealthMod = FMath::CeilToInt(HealthMod);
	return HealthMod;
}

void UDamageFunctionLibrary::SetDamageAttributes(const FGameplayEffectSpecHandle& SpecHandle, const FDamageAttributes& InAttributes)
{
	if (SpecHandle.Data.IsValid())
	{
		const auto SpecPtr = SpecHandle.Data.Get();
		SetDamageAttributesPtr(SpecPtr, InAttributes);
	}
}

void UDamageFunctionLibrary::SetDamageAttributesPtr(FGameplayEffectSpec* Spec, const FDamageAttributes& InAttributes)
{
	if (!Spec)
	{
		return;
	}
	
	Spec->SetSetByCallerMagnitude(Damage::BaseDamage, InAttributes.BaseDamage);
	Spec->SetSetByCallerMagnitude(Damage::BaseDamageFloating, InAttributes.DamageFloating);
	Spec->SetSetByCallerMagnitude(Damage::BaseCriticalRate, InAttributes.CriticalRate);
	Spec->SetSetByCallerMagnitude(Damage::BaseCriticalMultiplier, InAttributes.CriticalMultiplier);
}

float UDamageFunctionLibrary::EvaluateDamageViaGameplayEffect(const UAbilitySystemComponent* SourceASC,
                                                              TSubclassOf<UGameplayEffect> GEClass, const FDamageAttributes& InAttributes)
{
	if (!SourceASC || !GEClass) return 0.f;
	auto Context = SourceASC->MakeEffectContext();
	Context.AddInstigator(SourceASC->GetOwner(), SourceASC->GetOwner());
	FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(GEClass, 1, Context);
	FGameplayEffectSpec* Spec = SpecHandle.Data.Get();
	if (!Spec) return 0.f;

	SetDamageAttributesPtr(Spec, InAttributes);
	Spec->CalculateModifierMagnitudes();
	const auto ModifierMag = Spec->GetModifierMagnitude(0);

	return FMath::Abs(ModifierMag);
}

bool UDamageFunctionLibrary::IsCriticalDamage(const FGameplayTagContainer& TagContainer)
{
	return TagContainer.HasTag(Damage::IsCritical);
}
