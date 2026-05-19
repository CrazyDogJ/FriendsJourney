#include "Water/WaterBodyRiver_Buoyancy.h"

#include "WaterBodyRiverComponent.h"
#include "WaterSplineComponent.h"
#include "Components/AudioComponent.h"
#include "Water/WaterExtendFunctions.h"

AWaterBodyRiver_Buoyancy::AWaterBodyRiver_Buoyancy()
	: Super()
{
	PrimaryActorTick.bCanEverTick = true;
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("RiverAudio"));
	AudioComponent->SetOverrideAttenuation(true);
}

void AWaterBodyRiver_Buoyancy::Tick(float DeltaSeconds)
{
	const auto ClosestKey = FWaterExtendFunctions::GetClosestKey(GetWaterSpline());
	const auto Location = GetWaterSpline()->GetLocationAtSplineInputKey(ClosestKey, ESplineCoordinateSpace::World);
	const auto AudioIntensity = GetWaterBodyComponent()->GetAudioIntensityAtSplineInputKey(ClosestKey);
	const auto RiverWidth = Cast<UWaterBodyRiverComponent>(GetWaterBodyComponent())->GetRiverWidthAtSplineInputKey(ClosestKey);
	AudioComponent->SetWorldLocation(Location);
	AudioComponent->SetVolumeMultiplier(AudioIntensity);
	// Update attenuation.
	auto Cached = *AudioComponent->GetAttenuationSettingsToApply();
	Cached.AttenuationShapeExtents = FVector(RiverWidth + AttenuationExtentsOffset);
	Cached.FalloffDistance = FalloffDistance;
	AudioComponent->SetAttenuationOverrides(Cached);
}

void AWaterBodyRiver_Buoyancy::OnSurfaceTouchBegin_Native(UPrimitiveComponent* WaterComponent,
                                                          UPrimitiveComponent* SubmergedComponent, float SubmergedVolume, const FVector& SubmergedCenterOfMass,
                                                          const FVector& SubmergedVelocity)
{
}

void AWaterBodyRiver_Buoyancy::OnSurfaceTouching_Native(UPrimitiveComponent* WaterComponent,
	UPrimitiveComponent* SubmergedComponent, float SubmergedVolume, const FVector& SubmergedCenterOfMass,
	const FVector& SubmergedVelocity)
{
}

void AWaterBodyRiver_Buoyancy::OnSurfaceTouchEnd_Native(UPrimitiveComponent* WaterComponent,
	UPrimitiveComponent* SubmergedComponent, float SubmergedVolume, const FVector& SubmergedCenterOfMass,
	const FVector& SubmergedVelocity)
{
}
