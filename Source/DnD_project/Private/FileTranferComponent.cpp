// Copyright (c) Blizickij Vladimir. All rights reserved


#include "FileTranferComponent.h"
#include "Dice_PLayerState.h"
#include "Engine/World.h"
#include "Dice_GameState.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

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
    FString FilePath = SaveDir / OriginalFileName + TEXT(".png");

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

void UFileTranferComponent::DownloadFileFromURL(const FString& FileURL, const FString& LocalFileName)
{
    //HTTP запрос
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

    HttpRequest->SetTimeout(120); // для больших файлов - больше времени, может 120 - оверкилл
    HttpRequest->SetVerb("GET"); // можно указать разные методы, GET / POST
    HttpRequest->SetURL(FileURL);

    HttpRequest->OnProcessRequestComplete().BindLambda(
        [this, LocalFileName](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
        {
            this->OnDownloadComplete(Request, Response, bWasSuccessful, LocalFileName);
        }
    );

    //Отправка запроса
    HttpRequest->ProcessRequest();

    UE_LOG(LogTemp, Log, TEXT("Started downloading file from %s"), *FileURL);
}

void UFileTranferComponent::Multi_SyncronizeFiles_Implementation(const TArray<FString>& ImagesToSyncronize, const FString& ServerURL)
{
    if (GetOwnerRole() == ROLE_Authority)
    {
        return;
    }

    if (ImagesToSyncronize.IsEmpty())
    {
        UE_LOG(LogTemp, Log, TEXT("Downloadble image array is empty"));
        return;
    }

    for (auto& Element : ImagesToSyncronize)
    {
        FString paht = TEXT("Http://") / ServerURL / Element + TEXT(".png");

            DownloadFileFromURL(paht, Element);
    }
}

void UFileTranferComponent::OnDownloadComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, FString LocalFileName)
{
    if (bWasSuccessful && Response.IsValid() && Response->GetResponseCode() == 200)
    {
        TArray<uint8> FileData = Response->GetContent(); 

        SaveReceivedFile(FileData, LocalFileName);

        UE_LOG(LogTemp, Log, TEXT("File downloaded successfully from %s"), *Request->GetURL());
    }
    else
    {
        FString ErrorMessage = TEXT("Unknown error");
        if (!bWasSuccessful)
        {
            ErrorMessage = TEXT("Request failed");
        }
        else if (!Response.IsValid())
        {
            ErrorMessage = TEXT("Invalid response");
        }
        else
        {
            ErrorMessage = FString::Printf(TEXT("HTTP Error %d"), Response->GetResponseCode());
        }
        UE_LOG(LogTemp, Error, TEXT("File download failed from %s. Reason: %s"), *Request->GetURL(), *ErrorMessage);


        RecievingFile(false); 
    }
}