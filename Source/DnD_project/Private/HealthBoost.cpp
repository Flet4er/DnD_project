// Copyright (c) Blizickij Vladimir. All rights reserved


#include "HealthBoost.h"
#include "MyAttributeSet.h"

UHealthBoost::UHealthBoost()
{
    DurationPolicy = EGameplayEffectDurationType::Instant;

    //Modifiers = TArray<FGameplayModifierInfo>();
    FGameplayModifierInfo Modifier;// = Modifiers.AddDefaulted_GetRef();

    //FGameplayModifierInfo Modifier;
    Modifier.Attribute = UMyAttributeSet::GetHealthAttribute();
    Modifier.ModifierOp = EGameplayModOp::Additive;
    //Modifier.ModifierMagnitude = FScalableFloat(50.0f);
    FSetByCallerFloat SetByCallerFloat;
    SetByCallerFloat.DataTag = FGameplayTag::RequestGameplayTag(FName("Attribute.Health"));

    // Устанавливаем модификатор
    Modifier.ModifierMagnitude = FGameplayEffectModifierMagnitude(SetByCallerFloat);

    Modifiers.Add(Modifier);
}