// Copyright (c) Blizickij Vladimir. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Dice_CreaturePawn.generated.h"

UCLASS()
class DND_PROJECT_API ADice_CreaturePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADice_CreaturePawn();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* RootSceneComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MyMeshComponent;

	UFUNCTION()
	void OnMeshClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	UFUNCTION()
	void OnMeshReleased(UPrimitiveComponent* TouchedComponent, FKey ButtonReleased);
	UFUNCTION()
	void SetIsClicked(bool IsClicked);
	UFUNCTION()
	bool GetIsClicked();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY()
	bool bIsClicked = false;
	UPROPERTY()
	FHitResult HitResult;
	UPROPERTY()
	APlayerController* PawnOwner;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
