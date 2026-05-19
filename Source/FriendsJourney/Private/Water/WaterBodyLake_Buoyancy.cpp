#include "Water/WaterBodyLake_Buoyancy.h"

#include "WaterSplineComponent.h"
#include "Components/AudioComponent.h"
#include "Water/WaterExtendFunctions.h"

AWaterBodyLake_Buoyancy::AWaterBodyLake_Buoyancy()
	: Super()
{
	PrimaryActorTick.bCanEverTick = true;
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("LakeAudio"));
	AudioComponent->SetOverrideAttenuation(true);
}

void AWaterBodyLake_Buoyancy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	float ClosestKey;
	FVector ListenerLoc;
	const bool Inside = FWaterExtendFunctions::IsInsideSpline(this, GetWaterSpline(), ClosestKey, ListenerLoc);
	
	const auto Location = Inside ? FVector(ListenerLoc.X, ListenerLoc.Y, GetWaterBodyComponent()->GetConstantSurfaceZ()) :
		GetWaterSpline()->GetLocationAtSplineInputKey(ClosestKey, ESplineCoordinateSpace::World);
	const auto AudioIntensity = GetWaterBodyComponent()->GetAudioIntensityAtSplineInputKey(ClosestKey);
	
	AudioComponent->SetWorldLocation(Location);
	AudioComponent->SetVolumeMultiplier(AudioIntensity);
	// Update attenuation.
	auto Cached = *AudioComponent->GetAttenuationSettingsToApply();
	Cached.AttenuationShapeExtents = FVector(AttenuationExtents);
	Cached.FalloffDistance = FalloffDistance;
	AudioComponent->SetAttenuationOverrides(Cached);
}

void AWaterBodyLake_Buoyancy::OnSurfaceTouchBegin_Native(UPrimitiveComponent* WaterComponent,
                                                         UPrimitiveComponent* SubmergedComponent, float SubmergedVolume, const FVector& SubmergedCenterOfMass,
                                                         const FVector& SubmergedVelocity)
{
}

void AWaterBodyLake_Buoyancy::OnSurfaceTouching_Native(UPrimitiveComponent* WaterComponent,
	UPrimitiveComponent* SubmergedComponent, float SubmergedVolume, const FVector& SubmergedCenterOfMass,
	const FVector& SubmergedVelocity)
{
}

void AWaterBodyLake_Buoyancy::OnSurfaceTouchEnd_Native(UPrimitiveComponent* WaterComponent,
	UPrimitiveComponent* SubmergedComponent, float SubmergedVolume, const FVector& SubmergedCenterOfMass,
	const FVector& SubmergedVelocity)
{
}

void AWaterBodyLake_Buoyancy::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	GetWaterBodyComponent()->CurveSettings.ChannelDepth = LakeDepth;
}
