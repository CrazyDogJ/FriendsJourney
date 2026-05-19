// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "NativeGameplayTags.h"
#include "GMMC_Damage.generated.h"

namespace Damage
{
	FRIENDSJOURNEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(BaseDamage)
	FRIENDSJOURNEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(BaseDamageFloating)
	FRIENDSJOURNEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(BaseCriticalRate)
	FRIENDSJOURNEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(BaseCriticalMultiplier)
	FRIENDSJOURNEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(IsCritical)
}

UCLASS()
class UHitBoxPhysicalMaterial : public UPhysicalMaterial
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DamageMultiplier = 1.0f;
};

USTRUCT(BlueprintType)
struct FDamageAttributes
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseDamage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageFloating = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CriticalRate = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CriticalMultiplier = 1.0f;
};

UCLASS()
class FRIENDSJOURNEY_API UGMMC_Damage : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UGMMC_Damage();
	
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};

UCLASS()
class FRIENDSJOURNEY_API UDamageFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Damage")
	static void SetDamageAttributes(const FGameplayEffectSpecHandle& SpecHandle, const FDamageAttributes& InAttributes);

	static void SetDamageAttributesPtr(FGameplayEffectSpec* Spec, const FDamageAttributes& InAttributes);
	
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Damage")
	static float EvaluateDamageViaGameplayEffect(const UAbilitySystemComponent* SourceASC, TSubclassOf<UGameplayEffect> GEClass, const FDamageAttributes& InAttributes);
	
	UFUNCTION(BlueprintPure, Category = "Damage")
	static bool IsCriticalDamage(const FGameplayTagContainer& TagContainer);
};
