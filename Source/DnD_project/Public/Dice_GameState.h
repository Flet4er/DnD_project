// Copyright (c) Blizickij Vladimir. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "ImageSavedMasterStrct.h"
#include "Dice_GameState.generated.h"

/**
 * 
 */
UCLASS()
class DND_PROJECT_API ADice_GameState : public AGameState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Replicated)
	FString CurrentSessionName;
	
	UPROPERTY()
	bool InMainMenu;

	UFUNCTION()
	void SetInMainMenu(bool InMenu);

	UFUNCTION()
	bool GetInMainMenu();

	UFUNCTION()
	void SetSessionName(const FString& SessionName);

	UFUNCTION(BlueprintCallable)
	FString GetSessionName() const;

};

