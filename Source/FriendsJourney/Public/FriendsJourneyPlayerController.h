// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FriendsJourneyPlayerController.generated.h"

UCLASS()
class FRIENDSJOURNEY_API AFriendsJourneyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	APawn* CharacterPawn = nullptr;
	
protected:
	virtual void PawnLeavingGame() override;
};
