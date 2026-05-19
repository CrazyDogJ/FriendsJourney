// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AreaActorDetectLogic.generated.h"

class AAreaActorDetect;

UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class FRIENDSJOURNEY_API UAreaActorDetectLogic : public UObject
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	virtual bool ImplementsGetWorld() const override { return true; }
#endif
	
	UFUNCTION(BlueprintPure)
	AAreaActorDetect* GetOuterAreaActorDetect() const;
	
	UFUNCTION(BlueprintNativeEvent)
	TArray<AActor*> FilterCondition(const TArray<AActor*>& InActors) const;
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnOverlapStateChanged(bool HasInside);
};
