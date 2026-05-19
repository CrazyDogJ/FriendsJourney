// Fill out your copyright notice in the Description page of Project Settings.

#include "ZoneGraphAIController.h"

#include "MinimapZoneGraphAStar.h"
#include "NavigationPath.h"

AZoneGraphAIController::AZoneGraphAIController()
{
}

void AZoneGraphAIController::FindPathForMoveRequest(const FAIMoveRequest& MoveRequest, FPathFindingQuery& Query,
	FNavPathSharedPtr& OutPath) const
{
	Super::FindPathForMoveRequest(MoveRequest, Query, OutPath);

	if (!bEnableZoneGraphSearch)
	{
		return;
	}
	
	if (!OutPath.IsValid() || (OutPath.Get() && OutPath.Get()->IsPartial()))
	{
		FMinimapZoneGraphLanePath OutPathBP;
		const bool Valid = UMinimapZoneGraphAStarLibrary::GetZoneGraphPathBP(
			this, Query.StartLocation, Query.EndLocation, ZoneGraphSearchExtent, OutPathBP);

		// If path is valid
		if (Valid && OutPathBP.Path.Lanes.Num() > 0)
		{
			Query.EndLocation = OutPathBP.Path.StartLaneLocation.Position;
			Super::FindPathForMoveRequest(MoveRequest, Query, OutPath);
			if (OutPath.IsValid())
			{
				auto& Points = OutPath->GetPathPoints();
				TArray<FVector> OutZonePathPoints;
				if (UMinimapZoneGraphAStarLibrary::GetPathPoints(this, OutPathBP, OutZonePathPoints))
				{
					for (int i = 0; i < OutZonePathPoints.Num(); ++i)
					{
						if (i != 0)
						{
							Points.Add(FNavPathPoint(OutZonePathPoints[i]));
						}
					}
				}
			}
		}
	}
}
