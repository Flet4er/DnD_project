// Copyright (c) Blizickij Vladimir. All rights reserved

#include "ImageToByte.h"
#include "Engine/Texture2D.h"
#include "IImageWrapperModule.h"
#include "IImageWrapper.h"
#include "Modules/ModuleManager.h"


TArray<uint8> UImageToByte::ImageToBytes(UTexture2D* Texture)
{
	TArray<uint8> TextureBytes;

    if (!Texture || !Texture->GetPlatformData())
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid texture or platform data"));
        return TextureBytes;
    }

    // Получаем данные текстуры
    FTexture2DMipMap& Mip = Texture->GetPlatformData()->Mips[0];
    void* Data = Mip.BulkData.Lock(LOCK_READ_ONLY);
    int32 DataSize = Mip.BulkData.GetBulkDataSize();

    // Копируем данные в массив байтов
    TextureBytes.AddUninitialized(DataSize);
    FMemory::Memcpy(TextureBytes.GetData(), Data, DataSize);

    // Разблокируем данные
    Mip.BulkData.Unlock();

    return TextureBytes;
}

UTexture2D* UImageToByte::CreateTextureFromRawData(int32 Width, int32 Height, const TArray<uint8>& RawData)
{
    UTexture2D* NewTexture = UTexture2D::CreateTransient(Width, Height, PF_B8G8R8A8);
    if (!NewTexture)
        return nullptr;

    FTexture2DMipMap& Mip = NewTexture->GetPlatformData()->Mips[0];
    void* TextureData = Mip.BulkData.Lock(LOCK_READ_WRITE);
    FMemory::Memcpy(TextureData, RawData.GetData(), RawData.Num());
    Mip.BulkData.Unlock();

    NewTexture->SRGB = true;
    NewTexture->UpdateResource();

    return NewTexture;
}