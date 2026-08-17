// Fill out your copyright notice in the Description page of Project Settings.


#include "FeatureActions/GameFeatureAction_AddCharacter.h"

#include "FriendsJourneySubsystem.h"

void UGameFeatureAction_AddCharacter::AddAdditionalCharacters(const FWorldContext& WorldContext)
{
	UWorld* World = WorldContext.World();
	UGameInstance* GameInstance = WorldContext.OwningGameInstance;
	
	if ((GameInstance != nullptr) && (World != nullptr) && World->IsGameWorld())
	{
		if (UFriendsJourneySubsystem* Subsystem = UGameInstance::GetSubsystem<UFriendsJourneySubsystem>(GameInstance))
		{
			for (auto E : Characters)
			{
				Subsystem->AdditionalCharacters.AddUnique(E);
			}
		}
	}
}

void UGameFeatureAction_AddCharacter::RemoveAdditionalCharacters(const FWorldContext& WorldContext)
{
	UWorld* World = WorldContext.World();
	UGameInstance* GameInstance = WorldContext.OwningGameInstance;
	
	if ((GameInstance != nullptr) && (World != nullptr) && World->IsGameWorld())
	{
		if (UFriendsJourneySubsystem* Subsystem = UGameInstance::GetSubsystem<UFriendsJourneySubsystem>(GameInstance))
		{
			for (auto E : Characters)
			{
				Subsystem->AdditionalCharacters.Remove(E);
			}
		}
	}
}

void UGameFeatureAction_AddCharacter::HandleGameInstanceStart(UGameInstance* GameInstance,
	FGameFeatureStateChangeContext ChangeContext)
{
	if (FWorldContext* WorldContext = GameInstance->GetWorldContext())
	{
		if (ChangeContext.ShouldApplyToWorldContext(*WorldContext))
		{
			FContextHandles* Handles = ContextHandles.Find(ChangeContext);
			if (ensure(Handles))
			{
				AddAdditionalCharacters(*WorldContext);
			}
		}
	}
}

void UGameFeatureAction_AddCharacter::OnGameFeatureActivating(FGameFeatureActivatingContext& Context)
{
	Super::OnGameFeatureActivating(Context);
	
	FContextHandles& Handles = ContextHandles.FindOrAdd(Context);

	Handles.GameInstanceStartHandle = FWorldDelegates::OnStartGameInstance.AddUObject(this,
		&UGameFeatureAction_AddCharacter::HandleGameInstanceStart, FGameFeatureStateChangeContext(Context));
	
	for (const FWorldContext& WorldContext : GEngine->GetWorldContexts())
	{
		if (Context.ShouldApplyToWorldContext(WorldContext))
		{
			AddAdditionalCharacters(WorldContext);
		}
	}
}

void UGameFeatureAction_AddCharacter::OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context)
{
	Super::OnGameFeatureDeactivating(Context);
	
	FWorldDelegates::OnStartGameInstance.RemoveAll(this);
	
	for (const FWorldContext& WorldContext : GEngine->GetWorldContexts())
	{
		if (Context.ShouldApplyToWorldContext(WorldContext))
		{
			RemoveAdditionalCharacters(WorldContext);
		}
	}
}
