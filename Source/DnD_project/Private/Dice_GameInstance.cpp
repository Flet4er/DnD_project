// Copyright (c) Blizickij Vladimir. All rights reserved


#include "Dice_GameInstance.h"
#include "ImageUtils.h"
#include "ImageWriteBlueprintLibrary.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "PrimarySaveGame.h"
#include "Dice_GameState.h"

void UDice_GameInstance::Init()
{
	Super::Init();

	if (UGameplayStatics::DoesSaveGameExist(PrimarySaveSlot, 0))
	{
		PrimarySaveObject = Cast<UPrimarySaveGame>(UGameplayStatics::LoadGameFromSlot(PrimarySaveSlot, 0));

		UE_LOG(LogTemp, Log, TEXT("LoadedSaveGame with name = %s"), *PrimarySaveObject->GetName());
	}
	else
	{
		USaveGame* save = UGameplayStatics::CreateSaveGameObject(UPrimarySaveGame::StaticClass());
		UGameplayStatics::SaveGameToSlot(save, PrimarySaveSlot, 0);
		PrimarySaveObject = Cast<UPrimarySaveGame>(save);
		UE_LOG(LogTemp, Log, TEXT("New slot created with name = %s"), *PrimarySaveObject->GetName());
	}
	
}

UPrimarySaveGame* UDice_GameInstance::GetPrimaryGameObject()
{
	if (PrimarySaveObject)
	{
		return PrimarySaveObject;
	}
	else
	{
		PrimarySaveObject = Cast<UPrimarySaveGame>(UGameplayStatics::CreateSaveGameObject(UPrimarySaveGame::StaticClass()));
		return PrimarySaveObject;
	}
}

void UDice_GameInstance::SavePrimaryGameSlot(bool WhithoutAdding)
{
	if (WhithoutAdding)
	{
		UE_LOG(LogTemp, Log, TEXT("Just Saving Slot, no session created"));
	}
	else
	{
		Cast<UPrimarySaveGame>(PrimarySaveObject)->AllSavingSlots.Add(SessionName.ToString(), SessionName);
	}

	if (PrimarySaveObject)
	{
		UGameplayStatics::SaveGameToSlot(PrimarySaveObject, PrimarySaveSlot, 0);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Error while saving primary slot"));
	}
}

UDice_SaveGame* UDice_GameInstance::LoadGame(FString Slot)
{
	if (UGameplayStatics::DoesSaveGameExist(Slot, 0))
	{
		SaveObject = Cast<UDice_SaveGame>(UGameplayStatics::LoadGameFromSlot(Slot, 0));
		UE_LOG(LogTemp, Log, TEXT("Loaded SaveGame for image with name = %s"), *SaveObject->GetName());
		return SaveObject;
	}
	else 
	{
		SaveObject = Cast<UDice_SaveGame>(UGameplayStatics::CreateSaveGameObject(UDice_SaveGame::StaticClass()));
		UE_LOG(LogTemp, Log, TEXT("no save game for image, created with name  = %s"), *SaveObject->GetName());
		return SaveObject;
	}
	
}

bool UDice_GameInstance::LoadMainGame(FString Slot)
{
	TObjectPtr<UDice_SaveGame> savedgame = LoadGame(Slot);

	if(savedgame)
	{
		LoadImageFromDiskAndSet(savedgame->SavedImageStrct, savedgame);
		SetServerSessionName(FText::FromString(Slot));
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("CantLoadGame"));
		return false;
	}
	
}

void UDice_GameInstance::SaveGame(bool Override)
{
	if (UGameplayStatics::DoesSaveGameExist(GetCurrentSessionName().ToString(), 0))
	{
		if (Override)
		{
			UGameplayStatics::SaveGameToSlot(GetSaveGameObject(), GetCurrentSessionName().ToString(), 0);
			UE_LOG(LogTemp, Log, TEXT("SavingCompleteWithOverride"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("CantSaveOnSameSlot"));
		}
	}
	else
	{
		UGameplayStatics::SaveGameToSlot(GetSaveGameObject(), GetCurrentSessionName().ToString(), 0);
		UE_LOG(LogTemp, Log, TEXT("SavingComplete"));
		SavePrimaryGameSlot(false);
	}
}

void UDice_GameInstance::SetServerSessionName(FText Name)
{
	SessionName = Name;
}

void UDice_GameInstance::SetCurrentSessionName()
{
	Cast<ADice_GameState>(GetWorld()->GetGameState())->SetSessionName(SessionName.ToString());
}

FText UDice_GameInstance::GetCurrentSessionName()
{	
	return FText::FromString(Cast<ADice_GameState>(GetWorld()->GetGameState())->GetSessionName());
}

void UDice_GameInstance::LoadImageFromDiskAndSet(TArray<FImageSavedMasterStrct> TargetArray, UDice_SaveGame* SaveObj)
{
	if (!TargetArray.IsEmpty())
	{
		int32 _index = 0;
		for (auto& Element:TargetArray)
		{
			
			FText name = Element.FileName;
			FText sessionname = Element.SessionName;
			FString path = FPaths::ProjectDir() / CurrentSavePath / sessionname.ToString() / name.ToString() + TEXT(".png"); // Вот тут формат png, если делать по нормальному поддержку нескольких, то нужно и сохранять в других, пока так

			UE_LOG(LogTemp, Log, TEXT("Path  = %s"), *path);
			UTexture2D* image = LoadImageFromDisk(path);
			if (image)
			{
				UE_LOG(LogTemp, Log, TEXT("Name  = %s"), *name.ToString());
				SaveObj->SavedImageStrct[_index].FileName = name;
				SaveObj->SavedImageStrct[_index].Image = image;
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("ErrowWhileLoadingImageFromDisk"));
			}
			++_index;
		}
	}
	else
	{
		return;
	}
}

UTexture2D* UDice_GameInstance::LoadImageFromDisk(FString Filename)
{
	UE_LOG(LogTemp, Warning, TEXT("Calling LoadImageFromDisk with path: %s"), *Filename);
	UTexture2D* image = UKismetRenderingLibrary::ImportFileAsTexture2D(this, Filename);
	return image;
}

UDice_SaveGame* UDice_GameInstance::GetSaveGameObject()
{
	//UE_LOG(LogTemp, Log, TEXT("save game for image name  = %s"), *SaveObject->GetName());
	if (SaveObject)
	{
		return SaveObject;
	}
	else 
	{
		SaveObject = Cast<UDice_SaveGame>(UGameplayStatics::CreateSaveGameObject(UDice_SaveGame::StaticClass()));
		UE_LOG(LogTemp, Log, TEXT("created save game for image name  = %s"), *SaveObject->GetName());
		return SaveObject;
	}
}

void UDice_GameInstance::SaveImageOnDisk(UTexture2D* Image, FString Name)
{
	//UKismetRenderingLibrary::ExportTexture2D(this, Image, FPaths::ProjectDir() / CurrentSavePath, Name/TEXT(".png")); 
	FImageWriteOptions _options;
	_options.Format = EDesiredImageFormat::PNG;
	_options.bOverwriteFile = true;
	_options.CompressionQuality = 0;

	UImageWriteBlueprintLibrary::ExportToDisk(Image, FPaths::ProjectDir() / CurrentSavePath /GetCurrentSessionName().ToString()/ Name, _options);
}
