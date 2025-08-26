// Copyright (c) Blizickij Vladimir. All rights reserved

#include "Dice_GameState.h"
#include "Net/UnrealNetwork.h"

void ADice_GameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADice_GameState, CurrentSessionName);
}


void ADice_GameState::SetSessionName(const FString& SessionName)
{
	if (GetLocalRole() == ROLE_Authority)
	{
	UE_LOG(LogTemp, Log, TEXT("Set Session Name to %s"), *SessionName);
	CurrentSessionName = SessionName;
	}
}

FString ADice_GameState::GetSessionName() const
{
	UE_LOG(LogTemp, Log, TEXT("Get Session Name is %s"), *CurrentSessionName);
	return CurrentSessionName;
}
