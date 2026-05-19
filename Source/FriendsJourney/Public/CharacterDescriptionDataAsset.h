// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "CharacterDescriptionDataAsset.generated.h"

class UAlsMovementSettings_Extend;
class UGameplayAbility;
class UCharGameplayAttributeEvent;
class UCharGameplayTagEvent;
class UAbilitySystemComponent;
class UAlsMovementSettings;
class UGameplayEffect;
class UAlsFootstepEffectsSettings;
class UAlsCapsuleSizeSettings;

USTRUCT(BlueprintType)
struct FCharacterMeshDescription
{
	GENERATED_BODY()

	/** Soft object ptr for skeletal mesh. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<USkeletalMesh> SkeletalMesh = nullptr;

	/** Soft object ptr for anim class. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<UAnimInstance> AnimInstanceClass;

	/** Soft object ptr for outline materials. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSoftObjectPtr<UMaterialInterface>> OverlayMaterials;
};

USTRUCT(BlueprintType)
struct FCharacterStaticMeshDescription
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UStaticMesh> StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SocketName = NAME_None;
};

UCLASS(BlueprintType)
class FRIENDSJOURNEY_API UCharacterDescriptionDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CharacterId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	FText DisplayDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	FSlateBrush DisplayIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	FGameplayTag DisplayTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FCharacterMeshDescription MainMesh = FCharacterMeshDescription();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TArray<FCharacterMeshDescription> AdditionalMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TArray<FCharacterStaticMeshDescription> AdditionalStaticMeshes;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TSoftObjectPtr<UAlsCapsuleSizeSettings> CapsuleSizeSettings = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TSoftObjectPtr<UAlsFootstepEffectsSettings> FootstepEffectSettings = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TSoftObjectPtr<UAlsMovementSettings> MovementSettings = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TSoftObjectPtr<UAlsMovementSettings_Extend> MovementSettings_Extend = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Ability System")
	TMap<TSoftClassPtr<UGameplayAbility>, FGameplayTag> CharacterDefaultAbilities;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Ability System")
	TMap<TSoftClassPtr<UGameplayEffect>, float> CharacterDefaultEffects;

	/** Used to trigger some special event like sleeping, swimming to make some visual changes. */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Gameplay Ability System")
	TArray<TSoftClassPtr<UCharGameplayTagEvent>> GameplayTagEvents;

	/** Used for attribute base events. */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Gameplay Ability System")
	TArray<TSoftClassPtr<UCharGameplayAttributeEvent>> GameplayAttributeEvents;

	UFUNCTION(BlueprintCallable)
	void RegisterGameplayEvents(UAbilitySystemComponent* ASC, TArray<UCharGameplayTagEvent*>& OutGameplayTagEvents, TArray<UCharGameplayAttributeEvent*>& OutGameplayAttributeEvents);

	UFUNCTION(BlueprintCallable)
	void UnregisterGameplayEvents(UAbilitySystemComponent* ASC, TArray<UCharGameplayTagEvent*> InGameplayTagEvents, TArray<UCharGameplayAttributeEvent*> InGameplayAttributeEvents);
	
#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
