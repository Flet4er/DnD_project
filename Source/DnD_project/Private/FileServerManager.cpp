// Copyright (c) Blizickij Vladimir. All rights reserved


#include "FileServerManager.h"
#include "HttpServerModule.h"
#include "HttpPath.h"
#include "IHttpRouter.h"
#include "HttpServerRequest.h"
#include "HttpResultCallback.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "IPAddress.h" // Для получения IP сервера, если нужно
#include "Dice_GameState.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"

UFileServerManager::UFileServerManager()
{
    //ADice_GameState* MyGS = Cast<ADice_GameState>(GetWorld()->GetGameState());
    //PublicFilesDirectory = FPaths::ProjectSavedDir() / TEXT("SaveGames")/ MyGS->GetSessionName() ;
    //IFileManager::Get().MakeDirectory(*PublicFilesDirectory, true);
}

void UFileServerManager::BeginPlay()
{
    Super::BeginPlay();
    ADice_GameState* MyGS = Cast<ADice_GameState>(GetWorld()->GetGameState());
    PublicFilesDirectory = FPaths::ProjectSavedDir() / TEXT("SaveGames") / MyGS->GetSessionName();
}

bool UFileServerManager::StartServer(int32 Port)
{
    if (Route.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("HTTP Server is already running."));
        return false;
    }

    FHttpServerModule& HttpServerModule = FModuleManager::LoadModuleChecked<FHttpServerModule>("HttpServer");
    Route = HttpServerModule.GetHttpRouter(Port);
    if (!Route.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get HTTP Router on port %d."), Port);
        return false;
    }

    ListeningPort = Port;
    ADice_GameState* MyGS = Cast<ADice_GameState>(GetWorld()->GetGameState());

    //мб переделать в обычную функцию
    FHttpRequestHandler FileHandlerDelegate = FHttpRequestHandler::CreateLambda([this, MyGS](const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete) -> bool
    //auto FileHandler = [this](const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete) -> const FHttpRequestHandler
    {
            FString FileName = Request.RelativePath.GetPath();
            UE_LOG(LogTemp, Log, TEXT("HTTP Request for: %s"), *FileName);

            // Удаляем начальный слеш, если он есть
            if (FileName.StartsWith(TEXT("/")))
            {
                FileName.RemoveAt(0); // Удаляем первый символ '/'
            }
            UE_LOG(LogTemp, Log, TEXT("Attempting to serve file: %s"), *FileName);
            // Проверка на недопустимые символы в имени файла
            if (FileName.IsEmpty() || FileName.Contains("..") || FileName.Contains("/") || FileName.Contains("\\"))
            {
                UE_LOG(LogTemp, Warning, TEXT("Invalid file name requested: %s"), *FileName);

                TUniquePtr<FHttpServerResponse> Response = FHttpServerResponse::Create(TEXT("Invalid file name"), TEXT("text/plain"));
                if (Response)
                {
                    Response->Code = EHttpServerResponseCodes::BadRequest;
                    OnComplete(MoveTemp(Response));
                }
                return true;
            }

            // Формируем полный путь к файлу на сервере
            FString FullFilePath = FPaths::Combine(PublicFilesDirectory, FileName);
            UE_LOG(LogTemp, Log, TEXT("Trying to serve file: %s"), *FullFilePath);

            if (FPaths::FileExists(FullFilePath))
            {
                    TArray<uint8> FileData;
                    if (FFileHelper::LoadFileToArray(FileData, *FullFilePath))
                    {
                        // Определяем Content-Type (упрощенно)
                        FString Extension = FPaths::GetExtension(FileName).ToLower();
                        FString ContentType = TEXT("application/octet-stream"); // По умолчанию
                        if (Extension == TEXT("jpg") || Extension == TEXT("jpeg")) ContentType = TEXT("image/jpeg");
                        else if (Extension == TEXT("png")) ContentType = TEXT("image/png");
                        else if (Extension == TEXT("txt")) ContentType = TEXT("text/plain");

                        UE_LOG(LogTemp, Log, TEXT("File %s loaded, size: %d bytes"), *FileName, FileData.Num());

                        TUniquePtr<FHttpServerResponse> Response = FHttpServerResponse::Create(MoveTemp(FileData), ContentType);
                        if (Response.IsValid())
                        {
                            UE_LOG(LogTemp, Log, TEXT("Response created successfully. Code: %d"), static_cast<int>(Response->Code));
                            Response->Code = EHttpServerResponseCodes::Ok;
                            UE_LOG(LogTemp, Log, TEXT("Calling OnComplete..."));
                            OnComplete(MoveTemp(Response));
                        }
                        return true;
                    }
                    else
                    {
                        UE_LOG(LogTemp, Error, TEXT("Failed to read file: %s"), *FullFilePath);
                        TUniquePtr<FHttpServerResponse> Response = FHttpServerResponse::Create(TEXT("Failed to read file"), TEXT("text/plain"));
                        if (Response)
                        {
                            Response->Code = EHttpServerResponseCodes::ServerError;
                            OnComplete(MoveTemp(Response));
                        }
                        return true;
                    }
            }
            else
            {
                    UE_LOG(LogTemp, Warning, TEXT("File not found: %s"), *FullFilePath);
                    TUniquePtr<FHttpServerResponse> Response = FHttpServerResponse::Create(TEXT("File not found"), TEXT("text/plain"));
                    if (Response)
                    {
                        Response->Code = EHttpServerResponseCodes::NotFound;
                        OnComplete(MoveTemp(Response));
                    }
                    return true;
            }
            return true;
        });
    //FHttpPath HttpPath(FString("/") + MyGS->GetSessionName() + TEXT("/*"));
    FHttpPath HttpPath(FString("/") + MyGS->GetSessionName());
    Route->BindRoute(FHttpPath(HttpPath), EHttpServerRequestVerbs::VERB_GET, FileHandlerDelegate);


    HttpServerModule.StartAllListeners();

    UE_LOG(LogTemp, Log, TEXT("HTTP Server started on port %d serving files from %s"), Port, *PublicFilesDirectory);
    return true;
}

void UFileServerManager::StopServer()
{
    if (Route.IsValid())
    {
        FHttpServerModule& HttpServerModule = FModuleManager::LoadModuleChecked<FHttpServerModule>("HttpServer");
        // Останавливаем слушателя
        HttpServerModule.StopAllListeners();
        // Освобождаем роутер
        Route.Reset();
        UE_LOG(LogTemp, Log, TEXT("HTTP Server stopped."));
    }
}

FString UFileServerManager::GetServerURL() const
{
    if (Route.IsValid())
    {
        FString MyIP = TEXT("127.0.0.1"); //GetServerIP();

        UE_LOG(LogTemp, Log, TEXT("Server IP Address: %s"), *MyIP);

        ADice_GameState* MyGS = Cast<ADice_GameState>(GetWorld()->GetGameState());
        FString SessionName = MyGS->GetSessionName();

        UE_LOG(LogTemp, Log, TEXT("Server URL Address: %s"), *(MyIP / SessionName));
        return MyIP+TEXT(":") + FString::FromInt(ListeningPort) / SessionName;
    }
    return FString();
}

FString UFileServerManager::GetServerIP() const
{
    bool bCanBindAll;
    TSharedPtr<class FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLocalHostAddr(*GLog, bCanBindAll);
    FString MyIP = Addr->ToString(false);
    return MyIP;
}
