// Fill out your copyright notice in the Description page of Project Settings.


#include "AreaActorDetectLogic.h"

#include "AreaActorDetect.h"

TArray<AActor*> UAreaActorDetectLogic::FilterCondition_Implementation(const TArray<AActor*>& InActors) const
{
	return InActors;
}

AAreaActorDetect* UAreaActorDetectLogic::GetOuterAreaActorDetect() const
{
	return Cast<AAreaActorDetect>(GetOuter());
}
