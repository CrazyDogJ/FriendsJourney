// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "Abilities/Async/AbilityAsync.h"
#include "AbilityAsync_WaitAttributeChangedWithContext.generated.h"

class UAbilitySystemComponent;

UCLASS()
class FRIENDSJOURNEY_API UAbilityAsync_WaitAttributeChangedWithContext : public UAbilityAsync
{
	GENERATED_BODY()

public:

	/**
	 * Wait until the specified gameplay attribute is changed on a target ability system component
	 * It will keep listening as long as OnlyTriggerOnce = false
	 * If used in an ability graph, this async action will wait even after activation ends. It's recommended to use WaitForAttributeChange instead.
	 */
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DefaultToSelf = "TargetActor", BlueprintInternalUseOnly = "TRUE"))
	static UAbilityAsync_WaitAttributeChangedWithContext* WaitForAttributeChanged(AActor* TargetActor, FGameplayAttribute Attribute, bool OnlyTriggerOnce = false);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FAsyncWaitAttributeChangedDelegate, FGameplayAttribute, Attribute, float, NewValue, float, OldValue,
		FGameplayEffectSpec, EffectSpec, FGameplayModifierEvaluatedData, EvaluatedData);
	UPROPERTY(BlueprintAssignable)
	FAsyncWaitAttributeChangedDelegate Changed;

protected:

	virtual void Activate() override;
	virtual void EndAction() override;

	void OnAttributeChanged(const FOnAttributeChangeData& ChangeData);

	FGameplayAttribute Attribute;
	bool OnlyTriggerOnce = false;

	FDelegateHandle MyHandle;
};
