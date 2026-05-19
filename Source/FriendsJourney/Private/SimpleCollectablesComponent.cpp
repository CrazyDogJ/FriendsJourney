// Fill out your copyright notice in the Description page of Project Settings.

#include "SimpleCollectablesComponent.h"

#include "Net/UnrealNetwork.h"

void FCollectableList::AddCount(FGameplayTag CollectableTag, int Count)
{
	if (const auto Found = CollectableMap.Find(CollectableTag))
	{
		Found->Count += Count;
		CollectableEntries[Found->Index].Count += Count;
		MarkItemDirty(CollectableEntries[Found->Index]);
	}
	else
	{
		const auto NewEntry = FCollectableEntry(CollectableTag, Count);
		const auto Index = CollectableEntries.Add(NewEntry);
		MarkItemDirty(CollectableEntries[Index]);
		CollectableMap.Add(CollectableTag, FCollectableAccelerator(Index, Count));
	}
}

void FCollectableList::RemoveCount(FGameplayTag CollectableTag, int Count)
{
	if (const auto Found = CollectableMap.Find(CollectableTag))
	{
		Found->Count = FMath::Max(0, Found->Count - Count);
		CollectableEntries[Found->Index].Count = Found->Count;
		MarkItemDirty(CollectableEntries[Found->Index]);
	}
}

int FCollectableList::GetCount(FGameplayTag CollectableTag) const
{
	if (const auto Found = CollectableMap.Find(CollectableTag))
	{
		if (CollectableEntries.IsValidIndex(Found->Index))
		{
			return CollectableEntries[Found->Index].Count;
		}
	}
	
	return 0;
}

void FCollectableList::PreReplicatedRemove(const TArrayView<int32>& RemovedIndices, int32 FinalSize)
{
	for (const auto Index : RemovedIndices)
	{
		CollectableMap.Remove(CollectableEntries[Index].CollectableTag);
	}
}

void FCollectableList::PostReplicatedAdd(const TArrayView<int32>& AddedIndices, int32 FinalSize)
{
	for (const auto Index : AddedIndices)
	{
		CollectableMap.Add(CollectableEntries[Index].CollectableTag, FCollectableAccelerator(Index, CollectableEntries[Index].Count));
	}
}

void FCollectableList::PostReplicatedChange(const TArrayView<int32>& ChangedIndices, int32 FinalSize)
{
	for (const auto Index : ChangedIndices)
	{
		CollectableMap.Add(CollectableEntries[Index].CollectableTag, FCollectableAccelerator(Index, CollectableEntries[Index].Count));
	}
}

USimpleCollectablesComponent::USimpleCollectablesComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void USimpleCollectablesComponent::OnCollectableChangeMulticast_Implementation(const FGameplayTag Tag,
	const int ChangeCount, const int TotalCount)
{
	OnCollectableChange(Tag, ChangeCount, TotalCount);
}

void USimpleCollectablesComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, CollectableList)
}
