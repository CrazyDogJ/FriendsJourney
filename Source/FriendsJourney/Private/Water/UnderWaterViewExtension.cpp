// Fill out your copyright notice in the Description page of Project Settings.


#include "Water/UnderWaterViewExtension.h"
#include "SceneView.h"
#include "WaterRuntimeSettings.h"
#include "WaterSubsystem.h"

static int32 ForceViewUnderwater = 1;
static FAutoConsoleVariableRef CVarForceViewUnderwater(
	TEXT("r.Water.ForceViewUnderwater"),
	ForceViewUnderwater,
	TEXT("Should force view UnderwaterDepth to 1 and WaterIntersection to InsideWater to fix sky issue."
	  "-1 is disable all water view calc, 0 is default, 1 is ignore water exclusion volume, 2 is ignore all."),
	ECVF_Default
);



void FUnderwaterViewExtension::SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView)
{
	if (ForceViewUnderwater == -1)
	{
		InView.UnderwaterDepth = -1.0f;
		InView.WaterIntersection = EViewWaterIntersection::OutsideWater;
	}
	
	if (ForceViewUnderwater == 0)
	{
		return;
	}
	
	if (ForceViewUnderwater == 1 && OuterSubsystem)
	{
		TArray<FHitResult> Hits;
		const auto World = OuterSubsystem->GetWorld();
		if (const auto WaterBodyManager = UWaterSubsystem::GetWaterBodyManager(World))
		{
			static FCollisionQueryParams TraceSimple(SCENE_QUERY_STAT(DefaultQueryParam), false);
			const bool bWorldHasWater  = WaterBodyManager->HasAnyWaterBodies();
			if (bWorldHasWater && World->SweepMultiByChannel(Hits, InView.ViewLocation, 
				InView.ViewLocation - FVector(0, 0, 100), FQuat::Identity, 
				GetDefault<UWaterRuntimeSettings>()->CollisionChannelForWaterTraces, FCollisionShape::MakeSphere(100), TraceSimple))
			{
				if (Hits.Num() > 1)
				{
					InView.UnderwaterDepth = 1.0f;
					InView.WaterIntersection = EViewWaterIntersection::InsideWater;
				}
			}
		}
	}
	
	if (ForceViewUnderwater == 2)
	{
		InView.UnderwaterDepth = 1.0f;
		InView.WaterIntersection = EViewWaterIntersection::InsideWater;
		return;
	}
}