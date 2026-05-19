#pragma once

#include "CoreMinimal.h"
#include "BuoyancyEventInterface.h"
#include "WaterBodyOceanActor.h"
#include "WaterBodyOcean_Buoyancy.generated.h"

UCLASS(Blueprintable)
class FRIENDSJOURNEY_API AWaterBodyOcean_Buoyancy : public AWaterBodyOcean, public IBuoyancyEventInterface
{
	GENERATED_BODY()

public:
	AWaterBodyOcean_Buoyancy();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio")
	TObjectPtr<UAudioComponent> AudioComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Audio")
	float AttenuationExtents = 1000.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Audio")
	float FalloffDistance = 1000.0f;
	
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnSurfaceTouchBegin_Native(UPrimitiveComponent* WaterComponent, UPrimitiveComponent* SubmergedComponent, float SubmergedVolume, const FVector& SubmergedCenterOfMass, const FVector& SubmergedVelocity) override;
	virtual void OnSurfaceTouching_Native(UPrimitiveComponent* WaterComponent, UPrimitiveComponent* SubmergedComponent, float SubmergedVolume, const FVector& SubmergedCenterOfMass, const FVector& SubmergedVelocity) override;
	virtual void OnSurfaceTouchEnd_Native(UPrimitiveComponent* WaterComponent, UPrimitiveComponent* SubmergedComponent, float SubmergedVolume, const FVector& SubmergedCenterOfMass, const FVector& SubmergedVelocity) override;
};
