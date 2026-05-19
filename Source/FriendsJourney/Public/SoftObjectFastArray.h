// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "SoftObjectFastArray.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FSoftObejctArrayEvent, TSoftObjectPtr<UDataAsset>)

USTRUCT(BlueprintType)
struct FRIENDSJOURNEY_API FSoftObjectEntry : public FFastArraySerializerItem
{
	GENERATED_BODY()

	FSoftObjectEntry() {}

	explicit FSoftObjectEntry(const TSoftObjectPtr<UDataAsset>& InSoftDataAsset)
		: SoftDataAsset(InSoftDataAsset)
	{
	}

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TSoftObjectPtr<UDataAsset> SoftDataAsset;

	bool operator==(const FSoftObjectEntry& Other) const
	{
		return SoftDataAsset == Other.SoftDataAsset;
	}
};

USTRUCT(BlueprintType)
struct FRIENDSJOURNEY_API FSoftObjectList : public FFastArraySerializer
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<FSoftObjectEntry> SoftEntries;

	TArray<TSoftObjectPtr<UDataAsset>> GetPureArray() const;
	void SetFromArray(const TArray<TSoftObjectPtr<UDataAsset>>& InArray);
	bool AddUniqueSoftDataAsset(const TSoftObjectPtr<UDataAsset>& InAsset);
	bool RemoveSoftDataAsset(const TSoftObjectPtr<UDataAsset>& InAsset);

	void PostReplicatedChange(const TArrayView<int32>& ChangedIndices, int32 FinalSize);
	void PreReplicatedRemove(const TArrayView<int32>& RemovedIndices, int32 FinalSize);
	void PostReplicatedAdd(const TArrayView<int32>& AddedIndices, int32 FinalSize);

	FSoftObejctArrayEvent OnItemChanged;
	FSoftObejctArrayEvent OnItemAdded;
	FSoftObejctArrayEvent OnItemRemoved;
	
	// Replication
	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FSoftObjectEntry, FSoftObjectList>(SoftEntries, DeltaParams, *this);
	}
};

template<> struct TStructOpsTypeTraits<FSoftObjectList> : public TStructOpsTypeTraitsBase2<FSoftObjectList>
{
	enum { WithNetDeltaSerializer = true };
};

UCLASS()
class USoftDataAssetArrayLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static bool AddUniqueSoftDataAsset(UPARAM(ref) FSoftObjectList& List, const TSoftObjectPtr<UDataAsset>& SoftDataAsset);

	UFUNCTION(BlueprintCallable)
	static bool RemoveSoftDataAsset(UPARAM(ref) FSoftObjectList& List, const TSoftObjectPtr<UDataAsset>& SoftDataAsset);

	UFUNCTION(BlueprintCallable)
	static void SetFromArray(UPARAM(ref) FSoftObjectList& List, TArray<TSoftObjectPtr<UDataAsset>> SoftDataAssets);
	
	UFUNCTION(BlueprintCallable)
	static TArray<TSoftObjectPtr<UDataAsset>> GetPureArray(const FSoftObjectList& List);
};
