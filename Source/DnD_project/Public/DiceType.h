// Copyright (c) Blizickij Vladimir. All rights reserved


#pragma once

#include "CoreMinimal.h"
#include "DiceType.generated.h"
/**
 * 
 */
UENUM(BlueprintType)
enum class DiceTypeEnum : uint8
{
    d20 UMETA(DisplayName = "d20"),
    d12 UMETA(DisplayName = "d12"),
    d10 UMETA(DisplayName = "d10"),
    d8 UMETA(DisplayName = "d8"),
    d6 UMETA(DisplayName = "d6"),
    d4 UMETA(DisplayName = "d4"),
};
