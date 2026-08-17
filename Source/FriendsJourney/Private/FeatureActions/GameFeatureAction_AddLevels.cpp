// Fill out your copyright notice in the Description page of Project Settings.


#include "FeatureActions/GameFeatureAction_AddLevels.h"

#include "FriendsJourneySubsystem.h"
#include "GameFeaturesSubsystem.h"

void UGameFeatureAction_AddLevels::AddAdditionalLevels(const FWorldContext& WorldContext)
{
	UWorld* World = WorldContext.World();
	UGameInstance* GameInstance = WorldContext.OwningGameInstance;
	
	if ((GameInstance != nullptr) && (World != nullptr) && World->IsGameWorld())
	{
		if (UFriendsJourneySubsystem* Subsystem = UGameInstance::GetSubsystem<UFriendsJourneySubsystem>(GameInstance))
		{
			for (auto E : Levels)
			{
				Subsystem->AdditionalLevels.AddUnique(E);
			}
		}
	}
}

void UGameFeatureAction_AddLevels::RemoveAdditionalLevels(const FWorldContext& WorldContext)
{
	UWorld* World = WorldContext.World();
	UGameInstance* GameInstance = WorldContext.OwningGameInstance;
	
	if ((GameInstance != nullptr) && (World != nullptr) && World->IsGameWorld())
	{
		if (UFriendsJourneySubsystem* Subsystem = UGameInstance::GetSubsystem<UFriendsJourneySubsystem>(GameInstance))
		{
			for (auto E : Levels)
			{
				Subsystem->AdditionalLevels.Remove(E);
			}
		}
	}
}

void UGameFeatureAction_AddLevels::HandleGameInstanceStart(UGameInstance* GameInstance,
                                                           FGameFeatureStateChangeContext ChangeContext)
{
	if (FWorldContext* WorldContext = GameInstance->GetWorldContext())
	{
		if (ChangeContext.ShouldApplyToWorldContext(*WorldContext))
		{
			FContextHandles* Handles = ContextHandles.Find(ChangeContext);
			if (ensure(Handles))
			{
				AddAdditionalLevels(*WorldContext);
			}
		}
	}
}

void UGameFeatureAction_AddLevels::OnGameFeatureActivating(FGameFeatureActivatingContext& Context)
{
	Super::OnGameFeatureActivating(Context);
	
	FContextHandles& Handles = ContextHandles.FindOrAdd(Context);

	Handles.GameInstanceStartHandle = FWorldDelegates::OnStartGameInstance.AddUObject(this,
		&UGameFeatureAction_AddLevels::HandleGameInstanceStart, FGameFeatureStateChangeContext(Context));
	
	for (const FWorldContext& WorldContext : GEngine->GetWorldContexts())
	{
		if (Context.ShouldApplyToWorldContext(WorldContext))
		{
			AddAdditionalLevels(WorldContext);
		}
	}
}

void UGameFeatureAction_AddLevels::OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context)
{
	Super::OnGameFeatureDeactivating(Context);
	
	FWorldDelegates::OnStartGameInstance.RemoveAll(this);
	
	for (const FWorldContext& WorldContext : GEngine->GetWorldContexts())
	{
		if (Context.ShouldApplyToWorldContext(WorldContext))
		{
			RemoveAdditionalLevels(WorldContext);
		}
	}
}
