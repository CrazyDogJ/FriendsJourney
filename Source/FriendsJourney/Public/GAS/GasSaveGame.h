// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"
#include "GameFramework/SaveGame.h"
#include "GasSaveGame.generated.h"

class UGameplayEffect;

USTRUCT(BlueprintType)
struct FGameplayEffectSaveData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UGameplayEffect> EffectClass;
 
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 StackCount = 1;
 
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RemainingTime = 0.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTagContainer AssetTagContainer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTagContainer GrantedTagContainer;

	// TODO : Save context like who did this gameplay effect to target and so many things to SAVE AHHHHHHHHHHHHHHHHH!
	
	void InitFromSpec(const FGameplayEffectSpec& Spec, const float InRemainingTime)
	{
		RemainingTime = InRemainingTime;
		EffectClass = Spec.Def ? Spec.Def->GetClass() : nullptr;
		StackCount = Spec.GetStackCount();
		GrantedTagContainer = Spec.DynamicGrantedTags;
		AssetTagContainer = Spec.GetDynamicAssetTags();
	}

	FGameplayEffectSpec MakeSpec() const
	{
		auto NewSpec = FGameplayEffectSpec();
		NewSpec.Def = EffectClass.GetDefaultObject();
		NewSpec.SetStackCount(StackCount);
		NewSpec.DynamicGrantedTags = GrantedTagContainer;
		NewSpec.AppendDynamicAssetTags(AssetTagContainer);
		NewSpec.Duration = RemainingTime;
		
		return NewSpec;
	}
};

UCLASS()
class FRIENDSJOURNEY_API UGasSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, SaveGame)
	TMap<FGameplayAttribute, float> AttributeSaveDatas;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, SaveGame)
	TArray<FGameplayEffectSaveData> GameplayEffectSaveDatas;

	UFUNCTION(BlueprintCallable)
	bool SaveGas(UAbilitySystemComponent* Asc, TArray<FGameplayAttribute> AttributesToSave, FGameplayEffectQuery EffectQuery);

	UFUNCTION(BlueprintCallable)
	bool LoadGas(UAbilitySystemComponent* Asc);
};
