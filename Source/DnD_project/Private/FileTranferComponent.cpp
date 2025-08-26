// Copyright (c) Blizickij Vladimir. All rights reserved


#include "FileTranferComponent.h"
#include "Dice_PLayerState.h"
#include "Engine/World.h"
#include "Dice_GameState.h"

UFileTranferComponent::UFileTranferComponent()
{
    SetIsReplicatedByDefault(true);
}

void UFileTranferComponent::Client_ReceiveFileChunk_Implementation(const FFileChunk& Chunk)
{
    ADice_PlayerState* MyPS = Cast<ADice_PlayerState>(GetOuter());
    if (MyPS->GetOwningController()->GetLocalRole() == ROLE_Authority)
    {
        return;
    }

    if (Chunk.ChunkIndex == 0)
    {
        ReceivedFileData.Empty();
        ChunksReceived.Empty();
        ExpectedTotalChunks = Chunk.TotalChunks;
    }
    RecievingFile(true);
    ChunksReceived.Add(Chunk.ChunkIndex, Chunk.Data);

    if (ChunksReceived.Num() == Chunk.TotalChunks)
    {
        ReceivedFileData.Empty(Chunk.TotalFileSize);
        for (int32 i = 0; i < Chunk.TotalChunks; ++i)
        {
            if (ChunksReceived.Contains(i))
            {
                ReceivedFileData.Append(ChunksReceived[i]);
            }
        }

        SaveReceivedFile(ReceivedFileData, Chunk.OriginalFileName);
    }
}

void UFileTranferComponent::SaveReceivedFile(const TArray<uint8>& FileData, const FString& OriginalFileName)
{
    if (OriginalFileName.IsEmpty())
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid file name."));
        RecievingFile(false);
        return;
    }

    FString SessionName = Cast<ADice_GameState>(GetWorld()->GetGameState())->GetSessionName();
    FString SaveDir = FPaths::ProjectDir() / TEXT("Saved/SaveGames") / SessionName + TEXT("_client");
    FString FilePath = SaveDir / OriginalFileName;

    IFileManager::Get().MakeDirectory(*SaveDir, true);

    if (FFileHelper::SaveArrayToFile(FileData, *FilePath))
    {
        UE_LOG(LogTemp, Log, TEXT("File saved successfully: %s"), *FilePath);
        RecievingFile(false);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Error while saving file: %s"), *FilePath);
        RecievingFile(false);
    }
}
