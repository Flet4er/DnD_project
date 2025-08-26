// Copyright (c) Blizickij Vladimir. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PrimarySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class DND_PROJECT_API UPrimarySaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FText> AllSavingSlots;
};
