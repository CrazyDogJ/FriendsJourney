#pragma once

#include "CoreMinimal.h"
#include "BuoyancyEventInterface.h"
#include "WaterBodyLakeActor.h"
#include "WaterBodyLake_Buoyancy.generated.h"

UCLASS(Blueprintable)
class FRIENDSJOURNEY_API AWaterBodyLake_Buoyancy : public AWaterBodyLake, public IBuoyancyEventInterface
{
	GENERATED_BODY()

public:
	AWaterBodyLake_Buoyancy();

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

	/** Used to adjust lake depth when not affect landscape. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Collision")
	float LakeDepth = 500.0f;

	virtual void OnConstruction(const FTransform& Transform) override;
};
