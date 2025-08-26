// Copyright (c) Blizickij Vladimir. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ImageSavedMasterStrct.h"
#include "Dice_SaveGame.generated.h"

/**
 * 
 */
UCLASS()
class DND_PROJECT_API UDice_SaveGame : public USaveGame
{
	GENERATED_BODY()
public:	
	UPROPERTY(BlueprintReadWrite)
	TArray<FImageSavedMasterStrct> SavedImageStrct;
};
