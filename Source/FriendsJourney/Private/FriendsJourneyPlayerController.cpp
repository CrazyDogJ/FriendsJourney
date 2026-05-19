// Fill out your copyright notice in the Description page of Project Settings.

#include "FriendsJourneyPlayerController.h"

void AFriendsJourneyPlayerController::PawnLeavingGame()
{
	if (CharacterPawn && HasAuthority())
	{
		Possess(CharacterPawn);
	}
	
	Super::PawnLeavingGame();
}
