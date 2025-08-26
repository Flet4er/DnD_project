// Copyright (c) Blizickij Vladimir. All rights reserved

#include "DicePlayerController.h"
#include "FFileChunk.h"


/*
void ADicePlayerController::ClientReceiveFile_Implementation(const TArray<uint8>& FileData, const FText& FileName)
{
    FString FileNameStr = FileName.ToString();
    FString FilePath = FPaths::ProjectSavedDir() / TEXT("ReceivedFiles") / FileNameStr;

    IFileManager::Get().MakeDirectory(*FPaths::GetPath(FilePath), true);

    if (FFileHelper::SaveArrayToFile(FileData, *FilePath))
    {
        UE_LOG(LogTemp, Log, TEXT("File saved: %s"), *FilePath);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Errow while saving: %s"), *FilePath);
    }
}


void ADicePlayerController::Client_ReceiveFileChunk_Implementation(const FFileChunk& Chunk)
{
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

void ADicePlayerController::SaveReceivedFile(const TArray<uint8>& FileData, const FString& OriginalFileName)
{
    if (OriginalFileName.IsEmpty())
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid file name."));
        RecievingFile(false);
        return;
    }

    FString SaveDir = FPaths::ProjectSavedDir() / TEXT("Received");
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
*/