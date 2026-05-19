// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Navigation/NavLinkProxy.h"
#include "FriendsJourneyLibrary.generated.h"

class UClusterUnionComponent;
class UChaosVehicleMovementComponent;
class UImage;
/**
 * 
 */
UCLASS()
class FRIENDSJOURNEY_API UFriendsJourneyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static void RestartLevel(AGameModeBase* GameModeBase);

	/** Appends all tags granted by this gameplay effect spec */
	UFUNCTION(BlueprintCallable)
	static void GetAllGrantedTags(FGameplayEffectSpec InGeSpec, FGameplayTagContainer& OutContainer);

	/** Appends all blocked ability tags granted by this gameplay effect spec */
	UFUNCTION(BlueprintCallable)
	static void GetAllBlockedAbilityTags(FGameplayEffectSpec InGeSpec, FGameplayTagContainer& OutContainer);

	/** Appends all tags that apply to this gameplay effect spec */
	UFUNCTION(BlueprintCallable)
	static void GetAllAssetTags(FGameplayEffectSpec InGeSpec, FGameplayTagContainer& OutContainer);
	
	/** Appends all tags that apply to this gameplay effect spec */
	UFUNCTION(BlueprintPure)
	static AGameStateBase* GetGameStateBaseFromWorld(const FGameplayEffectSpec& InGeSpec);

	UFUNCTION(BlueprintPure)
	static void GetInstigator(const FGameplayEffectSpec& InGeSpec, AActor*& EffectCauser, AActor*& Instigator);
	
	UFUNCTION(BlueprintCallable)
	static void SetEffectContextHandle(UPARAM(ref)FGameplayEffectContextHandle& Handle, AController* Instigator, AActor* EffectCauser);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"))
	static void UpdateSessionPublicConnections(const UObject* WorldContextObject, const int NewPublicConnections);

	UFUNCTION(BlueprintCallable)
	static void ReleaseImageWidget(UImage* ImageWidget);

	UFUNCTION(BlueprintCallable)
	static void SetImageWidget(UImage* ImageWidget, UTexture2D* NewImage);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	static TArray<AActor*> GetTargetActors(const FGameplayAbilityTargetDataHandle& Handle);

	UFUNCTION(BlueprintPure)
	static bool IsPrimitiveComponentRendered(const UPrimitiveComponent* PrimitiveComponent);

	UFUNCTION(BlueprintPure)
	static FGameplayAbilityTargetDataHandle MakeTargetDataFromHitResults(const TArray<FHitResult>& HitResults);

	UFUNCTION(BlueprintCallable)
	static void SetSmartLinkOffset(ANavLinkProxy* NavLinkProxy, FVector Start, FVector End, bool bEnableActor = true, ENavLinkDirection::Type Direction = ENavLinkDirection::BothWays);

	UFUNCTION(BlueprintCallable)
	static void SetSmartLinkObstacle(ANavLinkProxy* NavLinkProxy, TSubclassOf<UNavArea> AreaClass, FVector BoxExtent, FVector BoxOffset);
};
