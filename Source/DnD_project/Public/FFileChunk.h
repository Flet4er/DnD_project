// Copyright (c) Blizickij Vladimir. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"
#include "FFileChunk.generated.h"

USTRUCT()
struct DND_PROJECT_API FFileChunk
{
    GENERATED_BODY()

    UPROPERTY()
    int32 TotalFileSize = 0;

    UPROPERTY()
    int32 ChunkIndex = 0;

    UPROPERTY()
    int32 TotalChunks = 0;

    UPROPERTY()
    TArray<uint8> Data;

    UPROPERTY()
    FString OriginalFileName;
};