// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FriendsJourneySubsystem.generated.h"

class UCharacterDescriptionDataAsset;

UCLASS()
class FRIENDSJOURNEY_API UFriendsJourneySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<TSoftObjectPtr<UWorld>> AdditionalLevels;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<TSoftObjectPtr<UCharacterDescriptionDataAsset>> AdditionalCharacters;
};
