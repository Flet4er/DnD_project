// Copyright (c) Blizickij Vladimir. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MyAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class DND_PROJECT_API UMyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UMyAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Health)

		//Attribute
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Strength)
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Dexterity)
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Constitution;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Constitution)
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Intelligence)
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Wisdom;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Wisdom)
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Charisma;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Charisma)
		
		//Skills
	UPROPERTY(BlueprintReadOnly, Category = "Skills")
	FGameplayAttributeData Acrobatics;//dex
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Acrobatics) 
	UPROPERTY(BlueprintReadOnly, Category = "Skills")
	FGameplayAttributeData Arcana; //int
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Arcana)
	UPROPERTY(BlueprintReadOnly, Category = "Skills")
	FGameplayAttributeData Athletics; //str
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Athletics)
	UPROPERTY(BlueprintReadOnly, Category = "Skills")
	FGameplayAttributeData Deception; //cha
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Deception)
	UPROPERTY(BlueprintReadOnly, Category = "Skills")
	FGameplayAttributeData History; //int
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, History)
	UPROPERTY(BlueprintReadOnly, Category = "Skills")
	FGameplayAttributeData Insight; //wis
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Insight)
	UPROPERTY(BlueprintReadOnly, Category = "Skills")
	FGameplayAttributeData Intimidation; //cha
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Intimidation)
	UPROPERTY(BlueprintReadOnly, Category = "Skills")
	FGameplayAttributeData Investigation; //int
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Investigation)
	UPROPERTY(BlueprintReadOnly, Category = "Skills")
	FGameplayAttributeData Medicine; //wis
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Medicine)
	UPROPERTY(BlueprintReadOnly, Category = "Skills")
	FGameplayAttributeData Nature; //int
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Nature)
	UPROPERTY(BlueprintReadOnly, Category = "Skills")
	FGameplayAttributeData Perception; //wis
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Perception)
	UPROPERTY(BlueprintReadOnly, Category = "Skills")
	FGameplayAttributeData Performance; //cha
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Performance)
	UPROPERTY(BlueprintReadOnly, Category = "Skills")
	FGameplayAttributeData Religion; //int
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Religion)
	UPROPERTY(BlueprintReadOnly, Category = "Skills")
	FGameplayAttributeData SleightHand; //dex
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, SleightHand)
	UPROPERTY(BlueprintReadOnly, Category = "Skills")
	FGameplayAttributeData Stealth; //dex
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Stealth) 
	UPROPERTY(BlueprintReadOnly, Category = "Skills")
	FGameplayAttributeData Survival; //wis
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Survival)

		//Second Attribute
	UPROPERTY(BlueprintReadOnly, Category = "Stat")
	FGameplayAttributeData CurrentHP;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, CurrentHP)
	UPROPERTY(BlueprintReadOnly, Category = "Stat")
	FGameplayAttributeData ArmourClass;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, ArmourClass)
	UPROPERTY(BlueprintReadOnly, Category = "Stat")
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Speed)
	UPROPERTY(BlueprintReadOnly, Category = "Stat")
	FGameplayAttributeData Initiative;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Initiative)


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	UFUNCTION()
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
};
