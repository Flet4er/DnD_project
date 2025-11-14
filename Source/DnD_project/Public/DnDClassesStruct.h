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
	Tiefling	UMETA(DisplayName = "Tiefling"),
};

UENUM(BlueprintType)
enum class EDnDStatsEnum : uint8
{
	Strength		UMETA(DisplayName = "Strength"),
	Dexterity		UMETA(DisplayName = "Dexterity"),
	Constitution	UMETA(DisplayName = "Constitution"),
	Intelligence	UMETA(DisplayName = "Intelligence"),
	Wisdom			UMETA(DisplayName = "Wisdom"),
	Charisma		UMETA(DisplayName = "Charisma"),
};

UENUM(BlueprintType)
enum class EDnDAttributesEnum : uint8
{
	Acrobatics		UMETA(DisplayName = "Acrobatics"),
	Arcana			UMETA(DisplayName = "Arcana"),
	Athletics		UMETA(DisplayName = "Athletics"),
	Deception		UMETA(DisplayName = "Deception"),
	History			UMETA(DisplayName = "History"),
	Insight			UMETA(DisplayName = "Insight"),
	Intimidation	UMETA(DisplayName = "Intimidation"),
	Investigation	UMETA(DisplayName = "Investigation"),
	Medicine		UMETA(DisplayName = "Medicine"),
	Nature			UMETA(DisplayName = "Nature"),
	Perception		UMETA(DisplayName = "Perception"),
	Performance		UMETA(DisplayName = "Performance"),
	Religion		UMETA(DisplayName = "Religion"),
	SleightHand		UMETA(DisplayName = "SleightHand"),
	Stealth			UMETA(DisplayName = "Stealth"),
	Survival		UMETA(DisplayName = "Survival"),
};

USTRUCT(BlueprintType)
struct DND_PROJECT_API FDnDClassesStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
	EDnDClassesEnum Class;

};
