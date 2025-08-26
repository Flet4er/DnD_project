// Copyright (c) Blizickij Vladimir. All rights reserved


#include "VerifyHashComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Dice_PLayerState.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "DicePlayerController.h"
#include "DiceGameMode.h"
#include <functional>
#include <sstream>

UVerifyHashComponent::UVerifyHashComponent()
{
    SetIsReplicatedByDefault(true);
}


FVerifyStruct UVerifyHashComponent::VerifyFiles(TArray<FImageSavedMasterStrct> InputArray)
{
    /*��� ��� ������������ ���� ��������� � ��������� ��� �����������(���\��������\���������)*/
    FVerifyStruct VerifyStruct;

    UE_LOG(LogTemp, Log, TEXT("VerifyFile in GameState Start"));
    if (InputArray.IsEmpty())
    {
        return VerifyStruct;
    }

    TArray<FString> NameArray;
    TArray<FString> HashArray;
    FString SessionName;
    for (auto& Element : InputArray)
    {
        FString path = FPaths::ProjectDir() / TEXT("Saved/SaveGames") / Element.SessionName.ToString() / Element.FileName.ToString() + TEXT(".png");
        HashArray.Add(LoadImageToHash(path));
        NameArray.Add(Element.FileName.ToString());
        SessionName = Element.SessionName.ToString();
    }
    

    VerifyStruct.HashArray = HashArray;
    VerifyStruct.NameArray = NameArray;
    VerifyStruct.SessionName = SessionName;

    //VerifyHashOnClient( NameArray, HashArray, SessionName);
    UE_LOG(LogTemp, Log, TEXT("VerifyFile sent struct to gamemode"));
    return VerifyStruct;
}

FString UVerifyHashComponent::LoadImageToHash(const FString Path)
{
    /*������� ��� �� �����*/
    TArray<uint8> FileData;
    if (!FFileHelper::LoadFileToArray(FileData, *Path))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load file: %s"), *Path);
        return TEXT("");
    }
    //������� � ������
    std::string DataString(reinterpret_cast<const char*>(FileData.GetData()), FileData.Num());

    //�������� ���
    std::hash<std::string> Hasher;
    size_t HashValue = Hasher(DataString);

    return FString::Printf(TEXT("%llu"), HashValue);
}

void UVerifyHashComponent::Client_VerifyHashOnClient_Implementation(const TArray<FString>& NameArray, const TArray<FString>& HashArray, const FString& SessionName)
{
    /* ���������� ��� ���� � ������� �� �����*/
    UE_LOG(LogTemp, Log, TEXT("VerifyHashOnClient_Implementation runing"));
    ADice_PlayerState* MyPS = Cast<ADice_PlayerState>(GetOuter());
    bool try1 = MyPS->GetOwningController()->IsLocalController();
    UE_LOG(LogTemp, Log, TEXT("VerifyHashOnClient_Implementation runing local? %hs"), try1? "true":"false");

    if (MyPS->GetOwningController()->GetLocalRole() == ROLE_AutonomousProxy)
    {
        UE_LOG(LogTemp, Log, TEXT("VerifyHashOnClient_Implementation ROLE_AutonomousProxy"));
        if (!NameArray.IsEmpty())
        {
            int32 Index = 0;
            for (auto& Element : NameArray)
            {
                FString path = FPaths::ProjectDir() / TEXT("Saved/SaveGames") / SessionName + TEXT("_client") / Element + TEXT(".png");
                if (LoadImageToHash(path) == HashArray[Index])
                {
                    UE_LOG(LogTemp, Log, TEXT("VerifyHashOnClient_Implementation %s Hash is Correct"), *path);
                }
                else
                {
                    FString path2 = FPaths::ProjectDir() / TEXT("Saved/SaveGames") / SessionName / Element + TEXT(".png");
                    UE_LOG(LogTemp, Log, TEXT("VerifyHashOnClient_Implementation %s Hash is inCorrect, need to download"), *path2);
                    Server_SendFileToClient(path2); //���������� ������� ������ �� �������� ����� �����
                }
                ++Index;
            }
        }

    }
    return;
}

void UVerifyHashComponent::Server_SendFileToClient_Implementation(const FString& PathToFile)
{
    /*��������� ������� ������� ����� ����� GameMode*/
    ADice_PlayerState* MyPS = Cast<ADice_PlayerState>(GetOuter());
    AController* MyPC= MyPS->GetOwningController();
    Cast<ADiceGameMode>(GetWorld()->GetAuthGameMode())->SendBigFileToClients(PathToFile);

}