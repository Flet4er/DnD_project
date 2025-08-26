// Copyright (c) Blizickij Vladimir. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ImageSavedMasterStrct.h"
#include "VerifyHashComponent.generated.h"

USTRUCT()
struct FVerifyStruct
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TArray<FString> NameArray;

	UPROPERTY()
	TArray<FString> HashArray;

	UPROPERTY()
	FString SessionName;
};

/*
конструктор поставил в Dice_PlayerState
*/
UCLASS()
class DND_PROJECT_API UVerifyHashComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UVerifyHashComponent();

	UFUNCTION()
	FString LoadImageToHash(const FString Path);

	UFUNCTION()
	FVerifyStruct VerifyFiles(TArray<FImageSavedMasterStrct> InputArray);

	UFUNCTION(Client, Reliable)
	void Client_VerifyHashOnClient(const TArray<FString>& NameArray, const TArray<FString>& HashArray, const FString& SessionName);

	UFUNCTION(Server, Reliable)
	void Server_SendFileToClient(const FString& PathToFile);
};

