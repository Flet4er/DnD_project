// Copyright (c) Blizickij Vladimir. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FFileChunk.h"
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

    /*
    TArray<uint8> ReceivedFileData;
    TMap<int32, TArray<uint8>> ChunksReceived;
    int32 ExpectedTotalChunks = 0;

	UFUNCTION(Client, Reliable)
	void ClientReceiveFile(const TArray<uint8>& FileData,const FText& FileName);

    UFUNCTION(BlueprintImplementableEvent)
    void RecievingFile(bool bIsRecieving);

    UFUNCTION(Client, Reliable)
    void Client_ReceiveFileChunk(const FFileChunk& Chunk);

    void SaveReceivedFile(const TArray<uint8>& FileData, const FString& OriginalFileName);
    */
};