// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GameplayAbility_Base.h"

void UGameplayAbility_Base::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);
	
	if (ActorInfo->PlayerController.IsValid())
	{
		if (ActorInfo->IsLocallyControlledPlayer())
		{
			OnLocallyControlled();
		}
	}
	
	// Controller change delegate.
	if (const auto Pawn = Cast<APawn>(ActorInfo->AvatarActor))
	{
		Pawn->ReceiveControllerChangedDelegate.AddUniqueDynamic(this, &ThisClass::ReceiveControllerChanged);
	}
	
	K2_OnAvatarSet(*ActorInfo, Spec);
}

void UGameplayAbility_Base::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo,
                                            const FGameplayAbilitySpec& Spec)
{
	if (const auto Pawn = Cast<APawn>(ActorInfo->AvatarActor))
	{
		Pawn->ReceiveControllerChangedDelegate.RemoveAll(this);
	}
	
	if (ActorInfo->IsLocallyControlledPlayer())
	{
		OnLocallyUncontrolled();
	}
	
	K2_OnRemoveAbility(*ActorInfo, Spec);
	
	Super::OnRemoveAbility(ActorInfo, Spec);
}

void UGameplayAbility_Base::ReceiveControllerChanged(APawn* Pawn, AController* OldController,
	AController* NewController)
{
	if (NewController && NewController->IsLocalPlayerController())
	{
		OnLocallyControlled();
	}
	else
	{
		OnLocallyUncontrolled();
	}
}
