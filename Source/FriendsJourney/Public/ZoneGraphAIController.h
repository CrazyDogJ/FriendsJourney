// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ZoneGraphAIController.generated.h"

UCLASS()
class FRIENDSJOURNEY_API AZoneGraphAIController : public AAIController
{
	GENERATED_BODY()

public:
	AZoneGraphAIController();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AI")
	bool bEnableZoneGraphSearch = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AI")
	FVector ZoneGraphSearchExtent = FVector(10000.0f);
	
	virtual void FindPathForMoveRequest(const FAIMoveRequest& MoveRequest, FPathFindingQuery& Query, FNavPathSharedPtr& OutPath) const override;
};
