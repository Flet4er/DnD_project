// Copyright (c) Blizickij Vladimir. All rights reserved


#include "Dice_PlayerState.h"
#include "UObject/UObjectGlobals.h"
#include "VerifyHashComponent.h"
#include "FileTranferComponent.h"

ADice_PlayerState::ADice_PlayerState()
{
	FileTransferComponent = CreateDefaultSubobject<UFileTranferComponent>(TEXT("TranferFiles"));
	VerifyHashComponent = CreateDefaultSubobject<UVerifyHashComponent>(TEXT("VerifyHash"));
}