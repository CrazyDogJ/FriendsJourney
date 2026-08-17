// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFeatureAction.h"
#include "GameFeaturesSubsystem.h"
#include "GameFeatureAction_AddCharacter.generated.h"

class UCharacterDescriptionDataAsset;

UCLASS()
class FRIENDSJOURNEY_API UGameFeatureAction_AddCharacter : public UGameFeatureAction
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSoftObjectPtr<UCharacterDescriptionDataAsset>> Characters;
	
	void AddAdditionalCharacters(const FWorldContext& WorldContext);
	void RemoveAdditionalCharacters(const FWorldContext& WorldContext);
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
