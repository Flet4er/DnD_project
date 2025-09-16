// Copyright (c) Blizickij Vladimir. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AbilityInputID.h"
#include "GameplayAbilitySet.h"
#include "AbilitySystemComponent.h"
#include "GA_Fireball.generated.h"

/**
 * 
 */
UCLASS()
class DND_PROJECT_API UGA_Fireball : public UGameplayAbility
{
	GENERATED_BODY()
    UGA_Fireball();

public:
	virtual void ActivateAbility(
        const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo,
        const FGameplayEventData* TriggerEventData) override;

    void ApplyFireballEffect(const FGameplayAbilityActorInfo* ActorInfo);

    TEnumAsByte<EGameplayAbilityInputBinds::Type> AbilityInputID;
};
