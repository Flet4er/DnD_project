// Copyright (c) Blizickij Vladimir. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DiceType.h"
#include "DiceCube_Base.generated.h"


UCLASS()
class DND_PROJECT_API ADiceCube_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADiceCube_Base();

	float DiceSize = 0.f;
	DiceTypeEnum DiceType;

protected:
	bool bIsBeenThrown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsGrabbed;
	static const TArray<FVector> D20Normals;
	TArray<class UTextRenderComponent*> TextRenders;
	TArray<class UArrowComponent*> Normals;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* DiceMesh;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void DiceD20init();
	void DiceStoped();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	float TimeDelay = 0.0f;
	float XDelayLocation;
	float YDelayLocation;
};
