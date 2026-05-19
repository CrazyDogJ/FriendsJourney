// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterDescriptionDataAsset.h"

#include "AbilitySystemComponent.h"
#include "CharGameplayTagEvent.h"
#include "CharGameplayAttributeEvent.h"

void UCharacterDescriptionDataAsset::RegisterGameplayEvents(UAbilitySystemComponent* ASC,
	TArray<UCharGameplayTagEvent*>& OutGameplayTagEvents,
	TArray<UCharGameplayAttributeEvent*>& OutGameplayAttributeEvents)
{
	if (!ASC)
	{
		return;
	}
	
	OutGameplayTagEvents.Empty();
	OutGameplayAttributeEvents.Empty();
	
	for (auto Itr : GameplayTagEvents)
	{
		auto NewObjectPtr = NewObject<UCharGameplayTagEvent>(ASC, Itr.LoadSynchronous());
		OutGameplayTagEvents.Add(NewObjectPtr);
		for (const auto ItrTag : NewObjectPtr->EventTag)
		{
			const auto Delegate = ASC->RegisterGameplayTagEvent(ItrTag, EGameplayTagEventType::NewOrRemoved).AddUObject(NewObjectPtr, &UCharGameplayTagEvent::OnTagChanged);
			NewObjectPtr->DelegateHandle.Add(ItrTag, Delegate);
		}
	}

	for (auto Itr : GameplayAttributeEvents)
	{
		auto NewObjectPtr = NewObject<UCharGameplayAttributeEvent>(ASC, Itr.LoadSynchronous());
		OutGameplayAttributeEvents.Add(NewObjectPtr);
		for (const auto ItrAttribute : NewObjectPtr->ListenAttribute)
		{
			ASC->GetGameplayAttributeValueChangeDelegate(ItrAttribute).AddUObject(NewObjectPtr, &UCharGameplayAttributeEvent::AttributeChanged);
			bool bFound;
			auto Value = ASC->GetGameplayAttributeValue(ItrAttribute, bFound);
			if (bFound)
			{
				NewObjectPtr->K2_OnAttributeChanged(ItrAttribute, 0.0f, Value);
			}
		}
	}
}

void UCharacterDescriptionDataAsset::UnregisterGameplayEvents(UAbilitySystemComponent* ASC,
	TArray<UCharGameplayTagEvent*> InGameplayTagEvents, TArray<UCharGameplayAttributeEvent*> InGameplayAttributeEvents)
{
	if (!ASC)
	{
		return;
	}
	
	for (const auto Itr : InGameplayTagEvents)
	{
		for (const auto Itr1 : Itr->DelegateHandle)
		{
			ASC->UnregisterGameplayTagEvent(Itr1.Value, Itr1.Key, EGameplayTagEventType::NewOrRemoved);
			Itr->ConditionalBeginDestroy();
		}
	}

	for (const auto Itr : InGameplayAttributeEvents)
	{
		for (const auto ItrAttribute : Itr->ListenAttribute)
		{
			ASC->GetGameplayAttributeValueChangeDelegate(ItrAttribute).RemoveAll(Itr);
			Itr->ConditionalBeginDestroy();
		}
	}

	InGameplayTagEvents.Empty();
	InGameplayAttributeEvents.Empty();
}

#if WITH_EDITOR
void UCharacterDescriptionDataAsset::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, CharacterId))
	{
		// Auto set up localization text.
		// DisplayName = FText::ChangeKey(TEXT("CharacterDescription"), CharacterId + "Name", DisplayName);
		DisplayDescription = FText::ChangeKey(TEXT("CharacterDescription"), CharacterId + "Description", DisplayDescription);
	}
}
#endif