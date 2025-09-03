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

    // �������� ������� URL ��� ������ (��������, "http://192.168.1.100:8080/files/")
    UFUNCTION(BlueprintCallable, Category = "HTTP Server")
    FString GetServerURL() const;

    UFUNCTION()
    FString GetServerIP() const;
protected:
    // ���������� ��� �������� /files/{filename}
    // ��� ����� ������� ��� ������, ���������� � BindRoute
    // void HandleFileRequest(const FHttpServerRequest& Request, const FHttpServerResponse& Response);

private:
    TSharedPtr<IHttpRouter> Route;
    int32 ListeningPort;
    FString PublicFilesDirectory; // ���� � ����� � �������, ��������, FPaths::ProjectSavedDir() / TEXT("ServedFiles")

};