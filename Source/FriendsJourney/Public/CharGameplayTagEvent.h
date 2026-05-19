// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharGameplayEvent.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "CharGameplayTagEvent.generated.h"

struct FGameplayTag;
class UAbilitySystemComponent;

UCLASS(Blueprintable)
class FRIENDSJOURNEY_API UCharGameplayTagEvent : public UCharGameplayEvent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Events")
	TArray<FGameplayTag> EventTag;
	
	TMap<FGameplayTag, FDelegateHandle> DelegateHandle;
	
	void OnTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void OnGameplayTagAdded(FGameplayTag Tag);

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void OnGameplayTagRemoved(FGameplayTag Tag);
};
