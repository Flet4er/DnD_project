// Copyright (c) Blizickij Vladimir. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FileServerManager.generated.h"

class IHttpRouter;
/**
 * 
 */
UCLASS()
class DND_PROJECT_API UFileServerManager : public UActorComponent
{
	GENERATED_BODY()

public:
    UFileServerManager();

    UFUNCTION()
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category = "HTTP Server")
    bool StartServer(int32 Port = 8080);

    UFUNCTION(BlueprintCallable, Category = "HTTP Server")
    void StopServer();

    // Получает базовый URL сервера типо такого: 127.0.0.1:8080/SessionName
    UFUNCTION(BlueprintCallable, Category = "HTTP Server")
    FString GetServerURL() const;

    UFUNCTION()
    FString GetServerIP() const;

private:
    TSharedPtr<IHttpRouter> Route;
    int32 ListeningPort;
    FString PublicFilesDirectory; 

};