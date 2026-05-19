// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AreaActorDetectLogic.h"
#include "GameFramework/Actor.h"
#include "AreaActorDetect.generated.h"

UCLASS()
class FRIENDSJOURNEY_API AAreaActorDetect : public AVolume
{
	GENERATED_UCLASS_BODY()

public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AActor> ActorFilter;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient)
	bool bHasActorInside = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced)
	UAreaActorDetectLogic* Logic = nullptr;
	
	UFUNCTION(BlueprintPure)
	bool HasActorInside() const;
 
protected:
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int OtherBodyIndex);
};
