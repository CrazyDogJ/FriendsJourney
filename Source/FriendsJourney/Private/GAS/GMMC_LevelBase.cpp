// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GMMC_LevelBase.h"

float UGMMC_LevelBase::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	return Spec.GetLevel();
}
