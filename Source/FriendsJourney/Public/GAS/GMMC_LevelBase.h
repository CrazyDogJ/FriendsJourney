// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "GMMC_LevelBase.generated.h"

/**
 * 
 */
UCLASS()
class FRIENDSJOURNEY_API UGMMC_LevelBase : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

protected:
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
