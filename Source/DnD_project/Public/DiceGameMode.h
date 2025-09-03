// Copyright (c) Blizickij Vladimir. All rights reserved

#pragma once

#include "FFileChunk.h"
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "FileServerManager.h"
#include "DiceGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DND_PROJECT_API ADiceGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	ADiceGameMode();

	UPROPERTY()
	int8 SendCount = 0;
	UPROPERTY()
	int8 SendCountMax = 8;

	UPROPERTY()
	FTimerHandle SendChunkTimerHandle;

	UPROPERTY()
	TArray<FString> FileSendQueue;

	UPROPERTY()
	bool bIsSending = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UFileServerManager* FileServerManagerComponent;

	TArray<FFileChunk> FileChunks;
	int32 CurrentChunkToSend;

	UFUNCTION()
	virtual void OnPostLogin(AController* NewPlayer) override;

	UFUNCTION(BlueprintImplementableEvent)
	void SendingFile(bool bSending);

	UFUNCTION(BlueprintCallable)
	void SynchronizeImageOnClients();

	UFUNCTION()
	TArray<FString> GetImageNameToSync();

	virtual void StartPlay();
	void StartSendingNextFile();

	UFUNCTION()
	void SendNextChunk();

    UFUNCTION(BlueprintCallable)
    void SendBigFileToClients(const FString& FilePath);

	UFUNCTION()
	void UnPauseMyTimer();
};

