// Copyright (c) Blizickij Vladimir. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"
#include "Engine/Texture2D.h"
#include "ImageSavedMasterStrct.generated.h"

USTRUCT(BlueprintType)
struct DND_PROJECT_API FImageSavedMasterStrct 
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FText SessionName;

	UPROPERTY(BlueprintReadWrite)
	FText FileName;

	UPROPERTY(BlueprintReadWrite)
	UTexture2D* Image;	
};
