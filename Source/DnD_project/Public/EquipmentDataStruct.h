// Copyright (c) Blizickij Vladimir. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameplayEffect.h"
#include "EquipmentDataStruct.generated.h"

USTRUCT(BlueprintType)
struct FDiceThrowDamage
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DiceNumber = 1; //how much dice throw

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "2"))
	int DiceEdgeNumber = 2; // how much edge dice can have, min of 2

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AddFlatDamage = 0; // flat damage adding after dice throw calculation
};

USTRUCT(BlueprintType)
struct DND_PROJECT_API FEquipmentDataStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	FGameplayTag Equipment;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	FText DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonuses")
	float Armour = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonuses")
	FDiceThrowDamage Damage; // используется формула 1d8+1 - кидается 1 дайс с 8 сторонами, то есть 1-8 разброс + 1 к результату

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TArray<TSubclassOf<UGameplayEffect>> GameplayEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Requirements")
	TArray<FGameplayTag> RequiredTags; //Race.Elf etc
};

