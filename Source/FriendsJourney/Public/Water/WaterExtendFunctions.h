// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

class UWaterSplineComponent;

class FRIENDSJOURNEY_API FWaterExtendFunctions
{
public:
	static FVector GetListenerLocation(const UObject* WorldContextObject);
	static float GetClosestKey(const UWaterSplineComponent* WaterSplineComponent);
	static bool IsInsideSpline(const UObject* WorldContextObject, const UWaterSplineComponent* WaterSplineComponent,
	                           float& ClosestKey, FVector& ListenerLoc);
};
