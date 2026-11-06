// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Water/UnderWaterViewExtension.h"
#include "FriendsJourneyWorldSubsystem.generated.h"

UCLASS()
class FRIENDSJOURNEY_API UFriendsJourneyWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	TSharedPtr<FUnderwaterViewExtension, ESPMode::ThreadSafe> ForceUnderwaterExt;
};
