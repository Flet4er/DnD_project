// Copyright (c) Blizickij Vladimir. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FFileChunk.h"
#include "Net/UnrealNetwork.h"
#include "HttpModule.h"
#include "FileTranferComponent.generated.h"


/*
конструктор поставил в Dice_PlayerState
*/
UCLASS()
class DND_PROJECT_API UFileTranferComponent : public UActorComponent
{
    
	GENERATED_BODY()
public:
    UFileTranferComponent();

    TArray<uint8> ReceivedFileData;
    TMap<int32, TArray<uint8>> ChunksReceived;
    int32 ExpectedTotalChunks = 0;

    UFUNCTION(BlueprintImplementableEvent)
    void RecievingFile(bool bIsRecieving);

    UFUNCTION(Client, Reliable)
    void Client_ReceiveFileChunk(const FFileChunk& Chunk);

    void SaveReceivedFile(const TArray<uint8>& FileData, const FString& OriginalFileName);

    UFUNCTION(BlueprintCallable, Category = "HTTP Download")
    void DownloadFileFromURL(const FString& FileURL, const FString& LocalFileName);

    UFUNCTION(NetMulticast,Reliable)
    void Multi_SyncronizeFiles(const TArray<FString>& ImagesToSyncronize, const FString& ServerURL);

protected:
    void OnDownloadComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, FString LocalFileName);
};