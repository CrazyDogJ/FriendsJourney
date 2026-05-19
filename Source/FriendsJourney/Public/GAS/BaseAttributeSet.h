// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "BaseAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

#define ATTRIBUTE_MAX_ADJUST(Attribute, NewValue, AttributeName, MaxAttributeName) \
		if (Attribute == Get##MaxAttributeName##Attribute()) AdjustAttributeForMaxChange(AttributeName, MaxAttributeName, NewValue, Get##AttributeName##Attribute());

#define ATTRIBUTE_MAX_SET(Data, AttributeName, MaxAttributeName) \
		float Clamped##AttributeName = FMath::Clamp(Get##AttributeName(), 0.0f, Get##MaxAttributeName()); \
		if (Data.EvaluatedData.Attribute == Get##AttributeName##Attribute() && Clamped##AttributeName != Get##AttributeName()) \
		{Set##AttributeName(FMath::Clamp(Get##AttributeName(), 0.0f, Get##MaxAttributeName()));}

UCLASS()
class FRIENDSJOURNEY_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UBaseAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(ThisClass, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(ThisClass, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_Damage)
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(ThisClass, Damage)

	UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_CriticalProbability)
	FGameplayAttributeData CriticalProbability;
	ATTRIBUTE_ACCESSORS(ThisClass, CriticalProbability)

	UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_CriticalMultiplier)
	FGameplayAttributeData CriticalMultiplier;
	ATTRIBUTE_ACCESSORS(ThisClass, CriticalMultiplier)
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void InitFromMetaDataTable(const UDataTable* DataTable) override;
	
protected:
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue) { GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Health, OldValue); }
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue) { GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxHealth, OldValue); }
	UFUNCTION()
	void OnRep_Damage(const FGameplayAttributeData& OldValue) { GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Damage, OldValue); }
	UFUNCTION()
	void OnRep_CriticalProbability(const FGameplayAttributeData& OldValue) { GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, CriticalProbability, OldValue); }
	UFUNCTION()
	void OnRep_CriticalMultiplier(const FGameplayAttributeData& OldValue) { GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, CriticalMultiplier, OldValue); }
};
