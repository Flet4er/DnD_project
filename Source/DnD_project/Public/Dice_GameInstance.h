// Copyright (c) Blizickij Vladimir. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PrimarySaveGame.h"
#include "Dice_SaveGame.h"
#include "Dice_GameInstance.generated.h"


/**
 * 
 */
UCLASS()
class DND_PROJECT_API UDice_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UPrimarySaveGame> PrimarySaveObject;
	UPROPERTY()
	TObjectPtr<UDice_SaveGame> SaveObject;
	FText SessionName;
	FString PrimarySaveSlot = TEXT("PrimaryGame");
	FString CurrentSavePath = TEXT("Saved/SaveGames");

	UFUNCTION()
	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	UPrimarySaveGame* GetPrimaryGameObject();
	
	UFUNCTION(BlueprintCallable)
	void SavePrimaryGameSlot(bool WithoutAdding);
	
	UFUNCTION()
	UDice_SaveGame* LoadGame(FString Slot);

	UFUNCTION(BlueprintCallable)
	bool LoadMainGame(FString Slot);

	UFUNCTION(BlueprintCallable)
	void SaveGame(bool Override);

	UFUNCTION(BlueprintCallable)
	void SetCurrentSessionName();

	UFUNCTION(BlueprintCallable)
	FText GetCurrentSessionName();

	UFUNCTION(BlueprintCallable)
	void SetServerSessionName(FText Name);
	UFUNCTION()
	void LoadImageFromDiskAndSet(TArray<FImageSavedMasterStrct> TargetArray, UDice_SaveGame* SaveObj);

	UFUNCTION()
	UTexture2D* LoadImageFromDisk(FString Filename);

	UFUNCTION(BlueprintCallable)
	UDice_SaveGame* GetSaveGameObject();

	UFUNCTION(BlueprintCallable)
	void SaveImageOnDisk(UTexture2D* Image, FString Name);


};
