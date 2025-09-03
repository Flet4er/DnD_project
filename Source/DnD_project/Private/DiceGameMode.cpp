// Copyright (c) Blizickij Vladimir. All rights reserved

#include "DiceGameMode.h"
#include "DicePlayerController.h"
#include "GameFramework/PlayerState.h"
#include "Dice_PlayerState.h"
#include "Dice_GameState.h"
#include "Dice_GameInstance.h"
#include "Containers/Queue.h"

ADiceGameMode::ADiceGameMode()
{
    FileServerManagerComponent = CreateDefaultSubobject<UFileServerManager>(TEXT("ServerManager"));

}
void ADiceGameMode::StartPlay()
{
    Super::StartPlay();
}

void ADiceGameMode::OnPostLogin(AController* NewPlayer)
{
    Super::OnPostLogin(NewPlayer);
    if (NewPlayer->GetLocalRole() == ROLE_Authority)
    {
        UDice_GameInstance* MyGI = Cast< UDice_GameInstance>(GetGameInstance());
        MyGI->SetCurrentSessionName();
    }
    UE_LOG(LogTemp, Log, TEXT("NewPlayerJoin: %s"), *NewPlayer->GetName());
}

TArray<FString> ADiceGameMode::GetImageNameToSync()
{
    UDice_GameInstance* MyGI = Cast< UDice_GameInstance>(GetGameInstance());
    if (MyGI)
    {
        UDice_SaveGame* SaveObject = MyGI->GetSaveGameObject();
        if (!SaveObject->SavedImageStrct.IsEmpty())
        {


            TArray<FImageSavedMasterStrct> TargetStruct = SaveObject->SavedImageStrct;
            TArray<FString> SyncArray;        
            for (auto& Element : TargetStruct)
            {
                SyncArray.Add(Element.FileName.ToString()); // странная хрень, наверно нужно добавлять изображение по текущей SessionName
            }
            return SyncArray;
        }
    }
    return TArray<FString>();
}
void ADiceGameMode::SynchronizeImageOnClients()
{
    TArray<FString> TargetArray = GetImageNameToSync();
    if (TargetArray.IsEmpty())
    {
        return;
    }

    for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
    {
        APlayerController* PC = Iterator->Get();
        if (PC && PC->IsLocalController())
        {
            ADicePlayerController* MyPC = Cast<ADicePlayerController>(PC);
            if (MyPC)
            {
                ADice_PlayerState* MyPS = MyPC->GetPlayerState<ADice_PlayerState>();
                if (MyPS)
                {
                    MyPS->FileTransferComponent->Multi_SyncronizeFiles(TargetArray, FileServerManagerComponent->GetServerURL());
                }
            }
        }
    }
}

void ADiceGameMode::SendBigFileToClients( const FString& FilePath)
{    
    FileSendQueue.Add(FilePath);
    UE_LOG(LogTemp, Log, TEXT("Add file to Queue"));

    if (!bIsSending)
    {
        StartSendingNextFile();
    }
}

void ADiceGameMode::StartSendingNextFile()
{
    //очередь
    if (FileSendQueue.Num() == 0)
    {
        UE_LOG(LogTemp, Log, TEXT("No files in queue to send."));
        bIsSending = false;

        SendingFile(bIsSending);

        return;
    }

    FString FilePath = FileSendQueue[0];
    FileSendQueue.RemoveAt(0); 

    FString FileName = FPaths::GetCleanFilename(FilePath);
    CurrentChunkToSend = 0;

    TArray<uint8> FileData;
    if (!FFileHelper::LoadFileToArray(FileData, *FilePath))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load file: %s"), *FilePath);
        StartSendingNextFile();
        return;
    }

    const int32 ChunkSize = 60000; //размер пакета данных (макс. около 63000)
    int32 TotalChunks = FMath::DivideAndRoundUp(FileData.Num(), ChunkSize);

    // чанк
    FileChunks.Empty();
    for (int32 i = 0; i < FileData.Num(); i += ChunkSize)
    {
        int32 CurrentChunkIndex = i / ChunkSize;
        int32 CurrentChunkSize = FMath::Min(ChunkSize, FileData.Num() - i);

        FFileChunk Chunk;
        Chunk.TotalFileSize = FileData.Num();
        Chunk.ChunkIndex = CurrentChunkIndex;
        Chunk.TotalChunks = TotalChunks;
        Chunk.Data.Append(&FileData[i], CurrentChunkSize);
        Chunk.OriginalFileName = FileName;

        FileChunks.Add(Chunk);
    }

    bIsSending = true;
    SendingFile(bIsSending);
    
    //добавить таймер на 1с после 5-10 отправок, что бы избежать переполнения очереди RPC
    GetWorld()->GetTimerManager().SetTimer(SendChunkTimerHandle, this, &ADiceGameMode::SendNextChunk, 0.2f, true); //если оверфловит, пакеты, увеличить задрежку таймера и возможно уменьшить размер пакета(ChunkSize)
}

void ADiceGameMode::SendNextChunk()
{


    if (CurrentChunkToSend >= FileChunks.Num())
    {
        GetWorld()->GetTimerManager().ClearTimer(SendChunkTimerHandle);
        bIsSending = false;
        SendingFile(bIsSending);

        StartSendingNextFile();
        return;
    }

    const FFileChunk& Chunk = FileChunks[CurrentChunkToSend];

    
    for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
    {
        APlayerController* PC = Iterator->Get();
        if (PC && !PC->IsLocalController())
        {
            ADicePlayerController* MyPC = Cast<ADicePlayerController>(PC);
            if (MyPC)
            {
                ADice_PlayerState* MyPS = MyPC->GetPlayerState<ADice_PlayerState>();
                if(MyPS)
                {
                    MyPS->FileTransferComponent->Client_ReceiveFileChunk(Chunk);
                }
            }
        }
    }   

    UE_LOG(LogTemp, Log, TEXT("Sent chunk %d of %d"), Chunk.ChunkIndex + 1, Chunk.TotalChunks);
    CurrentChunkToSend++;

    SendCount++;
    if (SendCount > SendCountMax)
    {
        GetWorld()->GetTimerManager().PauseTimer(SendChunkTimerHandle);
        FTimerHandle MyTimerHandle;
        GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &ADiceGameMode::UnPauseMyTimer, 2.f, false);
        SendCount = 0;
    }
}

void ADiceGameMode::UnPauseMyTimer()
{
    GetWorld()->GetTimerManager().UnPauseTimer(SendChunkTimerHandle);
}