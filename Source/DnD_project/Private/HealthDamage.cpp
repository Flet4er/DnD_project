// Copyright (c) Blizickij Vladimir. All rights reserved


#include "HealthDamage.h"
#include "MyAttributeSet.h"

UHealthDamage::UHealthDamage()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;

	FGameplayModifierInfo& Modifier = Modifiers.AddDefaulted_GetRef();
	Modifier.Attribute = UMyAttributeSet::GetHealthAttribute();
	Modifier.ModifierOp = EGameplayModOp::Additive;
	Modifier.ModifierMagnitude = FScalableFloat(-40.0f);
}