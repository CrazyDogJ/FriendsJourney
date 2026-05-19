// Fill out your copyright notice in the Description page of Project Settings.


#include "FriendsJourneyLibrary.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "NavLinkCustomComponent.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSessionSettings.h"
#include "Components/Image.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameSession.h"
#include "GameFramework/GameStateBase.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Runtime/Experimental/Chaos/Private/Chaos/PhysicsObjectInternal.h"

void UFriendsJourneyLibrary::RestartLevel(AGameModeBase* GameModeBase)
{
	if (!GameModeBase)
	{
		return;
	}
	
	if ( GameModeBase->GameSession->CanRestartGame() )
	{
		GameModeBase->GetWorld()->ServerTravel("?Restart",false);
	}
}

void UFriendsJourneyLibrary::GetAllGrantedTags(FGameplayEffectSpec InGeSpec, FGameplayTagContainer& OutContainer)
{
	InGeSpec.GetAllGrantedTags(OutContainer);
}

void UFriendsJourneyLibrary::GetAllBlockedAbilityTags(FGameplayEffectSpec InGeSpec, FGameplayTagContainer& OutContainer)
{
	InGeSpec.GetAllBlockedAbilityTags(OutContainer);
}

void UFriendsJourneyLibrary::GetAllAssetTags(FGameplayEffectSpec InGeSpec, FGameplayTagContainer& OutContainer)
{
	InGeSpec.GetAllAssetTags(OutContainer);
}

AGameStateBase* UFriendsJourneyLibrary::GetGameStateBaseFromWorld(const FGameplayEffectSpec& InGeSpec)
{
	if (const auto AbilitySystem = InGeSpec.GetEffectContext().GetInstigatorAbilitySystemComponent())
	{
		return AbilitySystem->GetWorld()->GetGameState();
	}

	return nullptr;
}

void UFriendsJourneyLibrary::GetInstigator(const FGameplayEffectSpec& InGeSpec, AActor*& EffectCauser, AActor*& Instigator)
{
	EffectCauser = InGeSpec.GetEffectContext().GetEffectCauser();
	Instigator = InGeSpec.GetEffectContext().GetInstigator();
}

void UFriendsJourneyLibrary::SetEffectContextHandle(FGameplayEffectContextHandle& Handle, AController* Instigator,
                                             AActor* EffectCauser)
{
	Handle.AddInstigator(Instigator, EffectCauser);
}

void UFriendsJourneyLibrary::UpdateSessionPublicConnections(const UObject* WorldContextObject, const int NewPublicConnections)
{
	const auto World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
	const auto OnlineSub = Online::GetSubsystem(World, NAME_None);
	const auto Sessions = OnlineSub->GetSessionInterface();
	if (Sessions.IsValid())
	{
		const FName SessionName = NAME_GameSession;
		FNamedOnlineSession* NamedSession = Sessions->GetNamedSession(SessionName);
		if (!NamedSession) return;

		// Add new slot for new player.
		NamedSession->SessionSettings.NumPublicConnections = NewPublicConnections;
		Sessions->UpdateSession(SessionName, NamedSession->SessionSettings, true);
		NamedSession->NumOpenPublicConnections = NewPublicConnections - World->GetGameState()->PlayerArray.Num();
	}
}

void UFriendsJourneyLibrary::ReleaseImageWidget(UImage* ImageWidget)
{
	if (!ImageWidget)
	{
		return;
	}
	
	if (const auto ResourceObject = ImageWidget->GetBrush().GetResourceObject())
	{
		ImageWidget->SetBrushFromTexture(nullptr);
		auto Copy = ImageWidget->GetBrush();
		Copy.DrawAs = ESlateBrushDrawType::Type::NoDrawType;
		ImageWidget->SetBrush(Copy);
		if (const auto CastTex = Cast<UTexture2D>(ResourceObject))
		{
			CastTex->ReleaseResource();
		}
	}
}

void UFriendsJourneyLibrary::SetImageWidget(UImage* ImageWidget, UTexture2D* NewImage)
{
	if (!ImageWidget || !NewImage)
	{
		return;
	}

	if (ImageWidget->GetBrush().GetResourceObject())
	{
		ReleaseImageWidget(ImageWidget);
	}

	auto Copy = ImageWidget->GetBrush();
	Copy.DrawAs = ESlateBrushDrawType::Type::Image;
	ImageWidget->SetBrush(Copy);
	
	NewImage->UpdateResource();
	ImageWidget->SetBrushResourceObject(NewImage);
}

TArray<AActor*> UFriendsJourneyLibrary::GetTargetActors(const FGameplayAbilityTargetDataHandle& Handle)
{
	TArray<AActor*> Result;
	for (const auto Itr : Handle.Data)
	{
		for (const auto ItrWeak : Itr->GetActors())
		{
			Result.Add(ItrWeak.Get());
		}
	}
	
	return Result;
}

bool UFriendsJourneyLibrary::IsPrimitiveComponentRendered(const UPrimitiveComponent* PrimitiveComponent)
{
	if (!PrimitiveComponent)
		return false;
	
	if (const UWorld* const World = PrimitiveComponent->GetWorld())
	{
		// Adjust tolerance, so visibility is not affected by bad frame rate / hitches.
		const float RenderTimeThreshold = FMath::Max(0.2f, World->DeltaTimeSeconds + UE_KINDA_SMALL_NUMBER);

		// If the current cached value is less than the tolerance then we don't need to go look at the components
		return World->TimeSince(PrimitiveComponent->GetLastRenderTimeOnScreen()) <= RenderTimeThreshold;
	}
	return false;
}

FGameplayAbilityTargetDataHandle UFriendsJourneyLibrary::MakeTargetDataFromHitResults(const TArray<FHitResult>& HitResults)
{
	FGameplayAbilityTargetDataHandle ReturnHandle;

	TArray<AActor*> HitActors;
	for (const FHitResult& Hit : HitResults)
	{
		if (!Hit.GetActor())
		{
			continue;
		}
		
		if (HitActors.Find(Hit.GetActor()) >= 0)
		{
			continue;
		}
		
		FGameplayAbilityTargetData_SingleTargetHit* NewData = new FGameplayAbilityTargetData_SingleTargetHit();
		NewData->HitResult = Hit;
		ReturnHandle.Add(NewData);
		HitActors.Add(Hit.GetActor());
	}
 
	return ReturnHandle;
}

void UFriendsJourneyLibrary::SetSmartLinkOffset(ANavLinkProxy* NavLinkProxy, const FVector Start, const FVector End, const bool bEnableActor, const ENavLinkDirection::Type Direction)
{
	if (NavLinkProxy)
	{
		if (bEnableActor)
		{
			NavLinkProxy->SetActorEnableCollision(true);
			NavLinkProxy->SetActorHiddenInGame(false);
		}
		
		NavLinkProxy->GetSmartLinkComp()->SetLinkData(Start, End, Direction);
	}
}

void UFriendsJourneyLibrary::SetSmartLinkObstacle(ANavLinkProxy* NavLinkProxy, TSubclassOf<UNavArea> AreaClass, FVector BoxExtent, FVector BoxOffset)
{
	if (NavLinkProxy)
	{
		NavLinkProxy->GetSmartLinkComp()->AddNavigationObstacle(AreaClass, BoxExtent, BoxOffset);
	}
}
