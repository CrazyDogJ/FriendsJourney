// Fill out your copyright notice in the Description page of Project Settings.


#include "AreaActorDetect.h"

#include "Components/BrushComponent.h"

AAreaActorDetect::AAreaActorDetect(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bColored = true;
	BrushColor.R = 100;
	BrushColor.G = 255;
	BrushColor.B = 100;
	BrushColor.A = 255;
	
	PrimaryActorTick.bCanEverTick = false;
	GetBrushComponent()->SetCollisionProfileName("OverlapAll");
	GetBrushComponent()->SetGenerateOverlapEvents(true);
	GetBrushComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	
	Logic = CreateDefaultSubobject<UAreaActorDetectLogic>(TEXT("Logic"));
}

bool AAreaActorDetect::HasActorInside() const
{
	TArray<AActor*> Actors;
	GetBrushComponent()->GetOverlappingActors(Actors, ActorFilter);
	if (Logic)
	{
		TArray<AActor*> FilteredActors = Logic->FilterCondition(Actors);
		return FilteredActors.Num() > 0;
	}
	
	return Actors.Num() > 0;
}

void AAreaActorDetect::BeginPlay()
{
	Super::BeginPlay();

	bHasActorInside = HasActorInside();

	if (Logic)
	{
		Logic->OnOverlapStateChanged(bHasActorInside);
	}
	
	GetBrushComponent()->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnComponentBeginOverlap);
	GetBrushComponent()->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnComponentEndOverlap);
}

void AAreaActorDetect::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetBrushComponent()->OnComponentBeginOverlap.RemoveAll(this);
	GetBrushComponent()->OnComponentEndOverlap.RemoveAll(this);
}

void AAreaActorDetect::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const bool Prev = bHasActorInside;
	bHasActorInside = HasActorInside();
	if (Logic && Prev != bHasActorInside)
	{
		Logic->OnOverlapStateChanged(bHasActorInside);
	}
}

void AAreaActorDetect::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	const bool Prev = bHasActorInside;
	bHasActorInside = HasActorInside();
	if (Logic && Prev != bHasActorInside)
	{
		Logic->OnOverlapStateChanged(bHasActorInside);
	}
}

