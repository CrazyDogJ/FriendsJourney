// Fill out your copyright notice in the Description page of Project Settings.


#include "SoftObjectFastArray.h"

TArray<TSoftObjectPtr<UDataAsset>> FSoftObjectList::GetPureArray() const
{
	TArray<TSoftObjectPtr<UDataAsset>> SoftObjects;
	for (const auto Itr : SoftEntries)
	{
		SoftObjects.Add(Itr.SoftDataAsset);
	}
	return SoftObjects;
}

void FSoftObjectList::SetFromArray(const TArray<TSoftObjectPtr<UDataAsset>>& InArray)
{
	// Set num.
	const auto Num = InArray.Num();
	// If item list is more than save data num.
	if (SoftEntries.Num() > Num)
	{
		for (int i = SoftEntries.Num() - 1; i >= Num; --i)
		{
			const auto CachedSoft = SoftEntries[i].SoftDataAsset;
			SoftEntries.RemoveAt(i);
			MarkArrayDirty();
			OnItemRemoved.Broadcast(CachedSoft);
		}
	}
	
	for (int i = 0; i < Num; ++i)
	{
		if (SoftEntries.IsValidIndex(i))
		{
			SoftEntries[i].SoftDataAsset = InArray[i];
			MarkItemDirty(SoftEntries[i]);
			OnItemChanged.Broadcast(InArray[i]);
		}
		else
		{
			SoftEntries.Add(FSoftObjectEntry(InArray[i]));
			MarkItemDirty(SoftEntries[i]);
			OnItemAdded.Broadcast(InArray[i]);
		}
	}
}

bool FSoftObjectList::AddUniqueSoftDataAsset(const TSoftObjectPtr<UDataAsset>& InAsset)
{
	if (InAsset.IsValid())
	{
		const auto FoundIndex = SoftEntries.Find(FSoftObjectEntry(InAsset));
		if (FoundIndex != INDEX_NONE)
		{
			return false;
		}

		auto NewEntry = FSoftObjectEntry(InAsset);
		SoftEntries.Add(NewEntry);
		MarkItemDirty(NewEntry);
		OnItemAdded.Broadcast(InAsset);
		return true;
	}

	return false;
}

bool FSoftObjectList::RemoveSoftDataAsset(const TSoftObjectPtr<UDataAsset>& InAsset)
{
	if (InAsset.IsValid())
	{
		if (SoftEntries.Remove(FSoftObjectEntry(InAsset)) > 0)
		{
			MarkArrayDirty();
			OnItemRemoved.Broadcast(InAsset);
			return true;
		}
	}

	return false;
}

void FSoftObjectList::PostReplicatedChange(const TArrayView<int32>& ChangedIndices, int32 FinalSize)
{
	for (const auto Index : ChangedIndices)
	{
		OnItemChanged.Broadcast(SoftEntries[Index].SoftDataAsset);
	}
}

void FSoftObjectList::PreReplicatedRemove(const TArrayView<int32>& RemovedIndices, int32 FinalSize)
{
	for (const auto Index : RemovedIndices)
	{
		OnItemRemoved.Broadcast(SoftEntries[Index].SoftDataAsset);
	}
}

void FSoftObjectList::PostReplicatedAdd(const TArrayView<int32>& AddedIndices, int32 FinalSize)
{
	for (const auto Index : AddedIndices)
	{
		OnItemAdded.Broadcast(SoftEntries[Index].SoftDataAsset);
	}
}

bool USoftDataAssetArrayLibrary::AddUniqueSoftDataAsset(FSoftObjectList& List,
	const TSoftObjectPtr<UDataAsset>& SoftDataAsset)
{
	return List.AddUniqueSoftDataAsset(SoftDataAsset);
}

bool USoftDataAssetArrayLibrary::RemoveSoftDataAsset(FSoftObjectList& List,
	const TSoftObjectPtr<UDataAsset>& SoftDataAsset)
{
	return List.RemoveSoftDataAsset(SoftDataAsset);
}

void USoftDataAssetArrayLibrary::SetFromArray(FSoftObjectList& List, TArray<TSoftObjectPtr<UDataAsset>> SoftDataAssets)
{
	List.SetFromArray(SoftDataAssets);
}

TArray<TSoftObjectPtr<UDataAsset>> USoftDataAssetArrayLibrary::GetPureArray(const FSoftObjectList& List)
{
	return List.GetPureArray();
}
