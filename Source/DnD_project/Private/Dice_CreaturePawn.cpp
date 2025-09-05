// Copyright (c) Blizickij Vladimir. All rights reserved


#include "Dice_CreaturePawn.h"

// Sets default values
ADice_CreaturePawn::ADice_CreaturePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
	SetRootComponent(RootSceneComponent);

	MyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("3DModels"));
	MyMeshComponent->SetupAttachment(RootSceneComponent);
	MyMeshComponent->OnClicked.AddDynamic(this, &ADice_CreaturePawn::OnMeshClicked);
	MyMeshComponent->OnReleased.AddDynamic(this, &ADice_CreaturePawn::OnMeshReleased);
}

// Called when the game starts or when spawned
void ADice_CreaturePawn::BeginPlay()
{
	Super::BeginPlay();

	PawnOwner = Cast<APlayerController>(GetOwner()); 	
}

// Called every frame
void ADice_CreaturePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//лучше заменить на Lerp
	if (GetIsClicked())
	{
		if (GetLocalRole() == ROLE_Authority)
		{
			GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(TraceTypeQuery1, false, HitResult);
			FVector Location = { HitResult.Location.X,HitResult.Location.Y, 95 }; // 95 - положение плоскости, пока захардкожено
			RootSceneComponent->SetWorldLocation(Location, false);
		}

		if (PawnOwner !=nullptr && PawnOwner->GetLocalRole() == ROLE_AutonomousProxy)
		{
			PawnOwner->GetHitResultUnderCursorByChannel(TraceTypeQuery1, false, HitResult);
			FVector Location = { HitResult.Location.X,HitResult.Location.Y, 95 }; // 95 - положение плоскости, пока захардкожено
			RootSceneComponent->SetWorldLocation(Location, false);
		}
	}
}

// Called to bind functionality to input
void ADice_CreaturePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADice_CreaturePawn::OnMeshClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	SetIsClicked(true);
	UE_LOG(LogTemp, Log, TEXT("Calling OnMeshClicked"));
}

void ADice_CreaturePawn::OnMeshReleased(UPrimitiveComponent* TouchedComponent, FKey ButtonReleased)
{
	SetIsClicked(false);
	UE_LOG(LogTemp, Log, TEXT("Calling OnMeshReleased"));
}

void ADice_CreaturePawn::SetIsClicked(bool IsClicked)
{
	this->bIsClicked = IsClicked;
}

bool ADice_CreaturePawn::GetIsClicked()
{
	return bIsClicked;
}
