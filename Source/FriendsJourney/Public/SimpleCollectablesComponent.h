// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "SimpleCollectablesComponent.generated.h"

USTRUCT(BlueprintType)
struct FRIENDSJOURNEY_API FCollectableEntry : public FFastArraySerializerItem
{
	GENERATED_BODY()

	FCollectableEntry() {}
	
	FCollectableEntry(const FGameplayTag InTag, const int InCount)
		: CollectableTag(InTag), Count(InCount)
	{
	}

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FGameplayTag CollectableTag;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int Count = 0;
};

USTRUCT()
struct FRIENDSJOURNEY_API FCollectableAccelerator
{
	GENERATED_BODY()
	
	UPROPERTY()
	int Index;
	
	UPROPERTY()
	int Count;
};

USTRUCT(BlueprintType)
struct FRIENDSJOURNEY_API FCollectableList : public FFastArraySerializer
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<FCollectableEntry> CollectableEntries;

	UPROPERTY(NotReplicated)
	TMap<FGameplayTag, FCollectableAccelerator> CollectableMap;

	void AddCount(FGameplayTag CollectableTag, int Count);
	void RemoveCount(FGameplayTag CollectableTag, int Count);
	int GetCount(FGameplayTag CollectableTag) const;
	
	void PreReplicatedRemove(const TArrayView<int32>& RemovedIndices, int32 FinalSize);
	void PostReplicatedAdd(const TArrayView<int32>& AddedIndices, int32 FinalSize);
	void PostReplicatedChange(const TArrayView<int32>& ChangedIndices, int32 FinalSize);
	
	// Replication
	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FCollectableEntry, FCollectableList>(CollectableEntries, DeltaParams, *this);
	}
};

template<> struct TStructOpsTypeTraits<FCollectableList> : public TStructOpsTypeTraitsBase2<FCollectableList>
{
	enum { WithNetDeltaSerializer = true };
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class FRIENDSJOURNEY_API USimpleCollectablesComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USimpleCollectablesComponent();

	UPROPERTY(Replicated, BlueprintReadOnly, VisibleAnywhere)
	FCollectableList CollectableList;

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	void AddCollectable(FGameplayTag Tag, int Count)
	{
		CollectableList.AddCount(Tag, Count);
		OnCollectableChangeMulticast(Tag, Count, GetCollectableCount(Tag));
	}

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	void RemoveCollectable(FGameplayTag Tag, int Count)
	{
		CollectableList.RemoveCount(Tag, Count);
		OnCollectableChangeMulticast(Tag, -Count, GetCollectableCount(Tag));
	}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetCollectableCount(FGameplayTag Tag) const
	{
		return CollectableList.GetCount(Tag);
	}

	UFUNCTION(NetMulticast, Unreliable)
	void OnCollectableChangeMulticast(const FGameplayTag Tag, const int ChangeCount, const int TotalCount);

	UFUNCTION(BlueprintImplementableEvent)
	void OnCollectableChange(const FGameplayTag Tag, const int ChangeCount, const int TotalCount);
	
protected:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};
