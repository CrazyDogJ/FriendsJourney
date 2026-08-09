// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbility_Base.generated.h"

UCLASS()
class FRIENDSJOURNEY_API UGameplayAbility_Base : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	
	virtual void OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	
	// Begin play (On ability give) function for ga.
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "On Avatar Set")
	void K2_OnAvatarSet(const FGameplayAbilityActorInfo ActorInfo, const FGameplayAbilitySpec& Spec);
	
	// End play function for ga.
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "On Remove Ability")
	void K2_OnRemoveAbility(const FGameplayAbilityActorInfo ActorInfo, const FGameplayAbilitySpec& Spec);
	
	// Used for ui display.
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "On Locally Controlled")
	void OnLocallyControlled();
	
	// Used for ui display.
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "On Locally Uncontrolled")
	void OnLocallyUncontrolled();
	
protected:
	UFUNCTION()
	void ReceiveControllerChanged(APawn* Pawn, AController* OldController, AController* NewController);
};
