// Copyright (c) Blizickij Vladimir. All rights reserved


#include "GA_Fireball.h"
#include "AbilitySystemComponent.h"
#include "HealthDamage.h"
#include "GameplayAbilitySet.h"
#include "Dice_CreaturePawn.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"


UGA_Fireball::UGA_Fireball()
{
    AbilityInputID = EGameplayAbilityInputBinds::Ability1;
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
     
    //добавляет новый тригер абилити через ивенты, для передачи данных через TriggerEventData
    FAbilityTriggerData TriggerData;
    TriggerData.TriggerTag = FGameplayTag::RequestGameplayTag(FName("Event.CastWithTargets"));
    TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
    AbilityTriggers.Add(TriggerData);
}

void UGA_Fireball::ActivateAbility(
    const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    // Проверяем возможность активации
    if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    if (TriggerEventData && TriggerEventData->TargetData.Num()>0)
    {
        TArray<AActor*> Targets =
            UAbilitySystemBlueprintLibrary::GetActorsFromTargetData(TriggerEventData->TargetData, 0);

        for (AActor* Target : Targets)
        {
            UE_LOG(LogTemp, Log, TEXT("Fireball target: %s"), *Target->GetName());
            FGameplayAbilityActorInfo* Trgt = Cast<ADice_CreaturePawn>(Target)->ASComponent->AbilityActorInfo.Get();
            // Тут логика способности
            ApplyFireballEffect(Trgt);
            //ApplyFireballEffect(ActorInfo);
        }
    }


    // Завершаем способность
    EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UGA_Fireball::ApplyFireballEffect(const FGameplayAbilityActorInfo* ActorInfo)
{
    UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
    if (!ASC) return;

    // Применяем эффект на ЦЕЛЬ
    FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
    FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(UHealthDamage::StaticClass(), 1.0f, Context);

    if (SpecHandle.IsValid())
    {
        ASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), ASC); //Каст на себя
    }
}