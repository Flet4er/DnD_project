// Copyright (c) Blizickij Vladimir. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FileTranferComponent.h"
#include "VerifyHashComponent.h"
#include "Dice_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class DND_PROJECT_API ADice_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:	
	ADice_PlayerState();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UFileTranferComponent* FileTransferComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UVerifyHashComponent* VerifyHashComponent;	
};
