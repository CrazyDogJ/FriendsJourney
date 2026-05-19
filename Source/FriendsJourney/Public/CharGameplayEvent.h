#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CharGameplayEvent.generated.h"

class UAbilitySystemComponent;

UCLASS()
class FRIENDSJOURNEY_API UCharGameplayEvent : public UObject
{
	GENERATED_BODY()

public:
	virtual class UWorld* GetWorld() const override;
#if WITH_EDITOR
	virtual bool ImplementsGetWorld() const override { return true; }
#endif
	
	UFUNCTION(BlueprintPure)
	UAbilitySystemComponent* GetOuterAbilitySystem() const;

	UFUNCTION(BlueprintPure)
	AActor* GetAvatarActor() const;
};
