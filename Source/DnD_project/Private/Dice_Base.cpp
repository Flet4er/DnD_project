// Copyright (c) Blizickij Vladimir. All rights reserved


#include "Dice_Base.h"

DEFINE_LOG_CATEGORY_STATIC(LogMyCategory, All, All);


// Sets default values
ADice_Base::ADice_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponentu"));
	SetRootComponent(StaticMeshComponent);
}

void ADice_Base::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (StaticMeshComponent)
	{
		StaticMeshComponent->SetStaticMesh(StatMesh1);
	}
}


int32 ADice_Base::GetMoney() const
{
	return Money;
}

int32 ADice_Base::GetMoney1_Implementation() const
{
	return Money;
}

// Called when the game starts or when spawned
void ADice_Base::BeginPlay()
{
	Super::BeginPlay();
	bool bIsVisible = false;
	int8 inative = -1;
	uint8 inative1 = 1;
	float row = .0f;
	const int16 inative2 = 25;
	FString ErrorName(TEXT("Error"));
	FName BoneName(TEXT("rad"));
	FText Description = FText::FromString(TEXT("Food"));

	FVector Location(.1,.1,.1);
	FRotator Rotation(.0, .0, .0);
	FTransform Tranfsorm(Rotation, Location, FVector::OneVector);

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Vector = %llu, %llu"), inative, inative1));

	UE_LOG(LogTemp, Display, TEXT("Some String"));
	UE_LOG(LogTemp, Display, TEXT("bIsVisible = %d"), bIsVisible);
	UE_LOG(LogTemp, Display, TEXT("bIsVisible = %i"), bIsVisible);
	UE_LOG(LogTemp, Display, TEXT("bIsVisible = %s"), bIsVisible? TEXT("True") : TEXT("False"));

	UE_LOG(LogTemp, Warning, TEXT("Some String"));
	UE_LOG(LogTemp, Error, TEXT("row = %f"), row);
	//UE_LOG(LogTemp, Fatal, TEXT("row = %f"), row); //������ � ���� ����� (���� ����������)

	UE_LOG(LogTemp, Error, TEXT("row = %f.2f"), row); //�������� ������

	UE_LOG(LogTemp, Warning, TEXT("Text print = %s"), *ErrorName); //��� ��������������� ������ ������ �������� *
	UE_LOG(LogTemp, Warning, TEXT("Text print = %s"), *BoneName.ToString());

	UE_LOG(LogTemp, Warning, TEXT("Text print = %s"), *Location.ToString());
	UE_LOG(LogMyCategory, Warning, TEXT("Text print = %s"), *Rotation.ToString());

}

// Called every frame
void ADice_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

