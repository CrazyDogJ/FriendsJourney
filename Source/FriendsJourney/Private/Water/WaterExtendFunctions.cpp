// Fill out your copyright notice in the Description page of Project Settings.


#include "Water/WaterExtendFunctions.h"

#include "WaterSplineComponent.h"

FVector FWaterExtendFunctions::GetListenerLocation(const UObject* WorldContextObject)
{
	const auto World = WorldContextObject->GetWorld();
	
	if (!World)
	{
		return FVector::ZeroVector;
	}
	
	if (const auto Player = World->GetFirstLocalPlayerFromController())
	{
		if (const auto PC = Player->PlayerController)
		{
			FVector ListenerPosition;
			FVector ListenerForward;
			FVector ListenerRight;
			PC->GetAudioListenerPosition(ListenerPosition, ListenerForward, ListenerRight);
			return ListenerPosition;
		}
	}

	return FVector::ZeroVector;
}

float FWaterExtendFunctions::GetClosestKey(const UWaterSplineComponent* WaterSplineComponent)
{
	if (!WaterSplineComponent)
	{
		return -1.0f;
	}
	
	const auto ListenerLoc = GetListenerLocation(WaterSplineComponent);
	return WaterSplineComponent->FindInputKeyClosestToWorldLocation(ListenerLoc);
}

bool FWaterExtendFunctions::IsInsideSpline(const UObject* WorldContextObject,
	const UWaterSplineComponent* WaterSplineComponent, float& ClosestKey, FVector& ListenerLoc)
{
	ListenerLoc = GetListenerLocation(WorldContextObject);
	ClosestKey = WaterSplineComponent->FindInputKeyClosestToWorldLocation(ListenerLoc);
	const auto SplinePointLoc = WaterSplineComponent->GetLocationAtSplineInputKey(ClosestKey, ESplineCoordinateSpace::World);
	const auto CamDirection = (ListenerLoc - SplinePointLoc).GetSafeNormal();
	const auto Right = WaterSplineComponent->GetRightVectorAtSplineInputKey(ClosestKey, ESplineCoordinateSpace::World);
	return FVector2D(CamDirection).Dot(FVector2D(Right)) > 0.0f;
}
