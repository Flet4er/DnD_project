// Copyright (c) Blizickij Vladimir. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "FileServerManager.generated.h"

/**
 * 
 */
UCLASS()
class DND_PROJECT_API UFileServerManager : public UObject
{
	GENERATED_BODY()

private:
	UFileServerManager();
	void StartServer();
};
