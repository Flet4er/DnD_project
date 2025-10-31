// Copyright (c) Blizickij Vladimir. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "DnDClassesStruct.generated.h"

UENUM(BlueprintType)
enum class EDnDClassesEnum : uint8
{
	Barbarian	UMETA(DisplayName = "Barbarian"),
	Bard		UMETA(DisplayName = "Bard"),
	Cleric		UMETA(DisplayName = "Cleric"),
	Druid		UMETA(DisplayName = "Druid"),
	Fighter		UMETA(DisplayName = "Fighter"),
	Monk		UMETA(DisplayName = "Monk"),
	Paladin		UMETA(DisplayName = "Paladin"),
	Ranger		UMETA(DisplayName = "Ranger"),
	Rogue		UMETA(DisplayName = "Rogue"),
	Sorcerer	UMETA(DisplayName = "Sorcerer"),
	Warlock		UMETA(DisplayName = "Warlock"),
	Wizard		UMETA(DisplayName = "Wizard")
};

UENUM(BlueprintType)
enum class EDnDRacesEnum : uint8
{
	Dragonborn	UMETA(DisplayName = "Dragonborn"),
	Dwarf		UMETA(DisplayName = "Dwarf"),
	Elf			UMETA(DisplayName = "Elf"),
	Gnome		UMETA(DisplayName = "Gnome"),
	Goliath		UMETA(DisplayName = "Goliath"),
	Halfling	UMETA(DisplayName = "Halfling"),
	Human		UMETA(DisplayName = "Human"),
	Orc			UMETA(DisplayName = "Orc"),
	Tiefling	UMETA(DisplayName = "Tiefling")

};

USTRUCT(BlueprintType)
struct DND_PROJECT_API FDnDClassesStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
	EDnDClassesEnum Class;

};

