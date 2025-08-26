// Copyright (c) Blizickij Vladimir. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "Modules/ModuleManager.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ImageToByte.generated.h"

/**
 * 
 */
UCLASS()
class DND_PROJECT_API UImageToByte : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable)
	static TArray<uint8> ImageToBytes(UTexture2D* Texture);

	UFUNCTION(BlueprintCallable)
	// Объявление функции
	static UTexture2D* CreateTextureFromRawData(int32 Width, int32 Height, const TArray<uint8>& RawData);
};
