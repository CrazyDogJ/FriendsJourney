#include "Water/WaterBodyOcean_Buoyancy.h"

#include "WaterSplineComponent.h"
#include "Components/AudioComponent.h"
#include "Water/WaterExtendFunctions.h"

AWaterBodyOcean_Buoyancy::AWaterBodyOcean_Buoyancy()
	: Super()
{
	PrimaryActorTick.bCanEverTick = true;
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("OceanAudio"));
	AudioComponent->SetOverrideAttenuation(true);
}

void AWaterBodyOcean_Buoyancy::Tick(float DeltaSeconds)
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

void AWaterBodyOcean_Buoyancy::OnSurfaceTouchBegin_Native(UPrimitiveComponent* WaterComponent,
                                                          UPrimitiveComponent* SubmergedComponent, float SubmergedVolume, const FVector& SubmergedCenterOfMass,
                                                          const FVector& SubmergedVelocity)
{
}

void AWaterBodyOcean_Buoyancy::OnSurfaceTouching_Native(UPrimitiveComponent* WaterComponent,
	UPrimitiveComponent* SubmergedComponent, float SubmergedVolume, const FVector& SubmergedCenterOfMass,
	const FVector& SubmergedVelocity)
{
}

void AWaterBodyOcean_Buoyancy::OnSurfaceTouchEnd_Native(UPrimitiveComponent* WaterComponent,
	UPrimitiveComponent* SubmergedComponent, float SubmergedVolume, const FVector& SubmergedCenterOfMass,
	const FVector& SubmergedVelocity)
{
}
