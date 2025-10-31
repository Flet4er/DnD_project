// Copyright (c) Blizickij Vladimir. All rights reserved

#include "DicePlayerController.h"
#include "FFileChunk.h"
#include "Dice_GameState.h"

void ADicePlayerController::BeginPlay()
{

	Super::BeginPlay();
	FString Level = GetWorld()->GetMapName();
	UE_LOG(LogTemp, Log, TEXT("Current Level i s %s"), *Level);
	if (Level.Contains(TEXT("MainMenu")))
	{
		Cast<ADice_GameState>(GetWorld()->GetGameState())->SetInMainMenu(true);
	}
	else
	{
		Cast<ADice_GameState>(GetWorld()->GetGameState())->SetInMainMenu(false);
	}
}
