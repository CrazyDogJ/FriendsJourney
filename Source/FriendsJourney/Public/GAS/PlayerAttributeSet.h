// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAttributeSet.h"
#include "PlayerAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class FRIENDSJOURNEY_API UPlayerAttributeSet : public UBaseAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Stamina", ReplicatedUsing = OnRep_Stamina)
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(ThisClass, Stamina)

	UPROPERTY(BlueprintReadOnly, Category = "Stamina", ReplicatedUsing = OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(ThisClass, MaxStamina)

	UPROPERTY(BlueprintReadOnly, Category = "Oxygen", ReplicatedUsing = OnRep_Oxygen)
	FGameplayAttributeData Oxygen;
	ATTRIBUTE_ACCESSORS(ThisClass, Oxygen)

	UPROPERTY(BlueprintReadOnly, Category = "Oxygen", ReplicatedUsing = OnRep_MaxOxygen)
	FGameplayAttributeData MaxOxygen;
	ATTRIBUTE_ACCESSORS(ThisClass, MaxOxygen)

	UPROPERTY(BlueprintReadOnly, Category = "Gauge", ReplicatedUsing = OnRep_Gauge)
	FGameplayAttributeData Gauge;
	ATTRIBUTE_ACCESSORS(ThisClass, Gauge)

	UPROPERTY(BlueprintReadOnly, Category = "Gauge", ReplicatedUsing = OnRep_MaxGauge)
	FGameplayAttributeData MaxGauge;
	ATTRIBUTE_ACCESSORS(ThisClass, MaxGauge)

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldValue) { GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Stamina, OldValue); }
	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& OldValue) { GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxStamina, OldValue); }
	UFUNCTION()
	void OnRep_Oxygen(const FGameplayAttributeData& OldValue) { GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Oxygen, OldValue); }
	UFUNCTION()
	void OnRep_MaxOxygen(const FGameplayAttributeData& OldValue) { GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxOxygen, OldValue); }
	UFUNCTION()
	void OnRep_Gauge(const FGameplayAttributeData& OldValue) { GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Gauge, OldValue); }
	UFUNCTION()
	void OnRep_MaxGauge(const FGameplayAttributeData& OldValue) { GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxGauge, OldValue); }
};
