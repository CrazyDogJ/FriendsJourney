// Fill out your copyright notice in the Description page of Project Settings.


#include "FriendsJourneyWorldSubsystem.h"

void UFriendsJourneyWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	ForceUnderwaterExt = FSceneViewExtensions::NewExtension<FUnderwaterViewExtension>();
	ForceUnderwaterExt->OuterSubsystem = this;
}

void UFriendsJourneyWorldSubsystem::Deinitialize()
{
	ForceUnderwaterExt->OuterSubsystem = nullptr;
	ForceUnderwaterExt.Reset();
	
	Super::Deinitialize();
}
