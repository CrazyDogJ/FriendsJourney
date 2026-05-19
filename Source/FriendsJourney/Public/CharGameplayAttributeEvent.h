// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "CharGameplayEvent.h"
#include "GameplayEffectTypes.h"
#include "UObject/Object.h"
#include "CharGameplayAttributeEvent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FRIENDSJOURNEY_API UCharGameplayAttributeEvent : public UCharGameplayEvent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attribute")
	TArray<FGameplayAttribute> ListenAttribute;
	
	void AttributeChanged(const FOnAttributeChangeData& Data);

	UFUNCTION(BlueprintImplementableEvent, Category = "Attribute", DisplayName = "On Attribute Changed")
	void K2_OnAttributeChanged(FGameplayAttribute Attribute, float OldValue, float NewValue);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Attribute")
	void Tick(float DeltaTime);
};
