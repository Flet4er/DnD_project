// Copyright (c) Blizickij Vladimir. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Dice_Base.generated.h"

UCLASS()
class DND_PROJECT_API ADice_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int FacesNumber;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	int FacesNumber1;

	UPROPERTY(BlueprintReadOnly)
	float FacesNumber2;

	UPROPERTY(BlueprintReadWrite)
	float FacesNumber3;

	UPROPERTY(EditDefaultsOnly)
	float FacesNumber5;

	UPROPERTY(EditAnywhere)
	UStaticMesh* StatMesh;

	UPROPERTY(EditAnywhere, Category = "Def|Sub")
	UStaticMesh* StatMesh1;

	int32 Money;

	UFUNCTION(BlueprintCallable)
	int32 GetMoney() const;

	UFUNCTION(BlueprintPure, BlueprintNativeEvent)
	int32 GetMoney1() const;

	ADice_Base();
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
