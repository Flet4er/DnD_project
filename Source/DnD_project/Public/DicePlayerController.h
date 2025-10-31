// Copyright (c) Blizickij Vladimir. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FFileChunk.h"
#include "Dice_CreaturePawn.h"
#include "DicePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DND_PROJECT_API ADicePlayerController : public APlayerController
{
	GENERATED_BODY()
public:

    UFUNCTION(BlueprintImplementableEvent)
    void FCKNGTEST();

	UFUNCTION(BlueprintImplementableEvent)
	void AddToHeroPanel(ADice_CreaturePawn* Hero);
protected:

	virtual void BeginPlay() override;
};