// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFeatureAction.h"
#include "GameFeaturesSubsystem.h"

#include "GameFeatureAction_AddLevels.generated.h"

UCLASS()
class FRIENDSJOURNEY_API UGameFeatureAction_AddLevels : public UGameFeatureAction
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSoftObjectPtr<UWorld>> Levels;
	
	void AddAdditionalLevels(const FWorldContext& WorldContext);
	void RemoveAdditionalLevels(const FWorldContext& WorldContext);
	void HandleGameInstanceStart(UGameInstance* GameInstance, FGameFeatureStateChangeContext GameFeatureStateChangeContext);
	virtual void OnGameFeatureActivating(FGameFeatureActivatingContext& Context) override;
	virtual void OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context) override;
	
private:
	struct FContextHandles
	{
		FDelegateHandle GameInstanceStartHandle;
	};
	
	TMap<FGameFeatureStateChangeContext, FContextHandles> ContextHandles;
};
