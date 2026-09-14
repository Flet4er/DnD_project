// Copyright (c) Blizickij Vladimir. All rights reserved


#include "DiceCube_Base.h"
#include "DiceType.h"
#include "Components/TextRenderComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/EngineTypes.h"

// Sets default values
ADiceCube_Base::ADiceCube_Base()
{
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADiceCube_Base::BeginPlay()
{
	Super::BeginPlay();
	
	switch (DiceType)
	{
	case DiceTypeEnum::d20:
		DiceD20init();
		break;

	case DiceTypeEnum::d12:
		//d12
		break;

	case DiceTypeEnum::d10:
		//d10
		break;

	case DiceTypeEnum::d8:
		//
		break;

	case DiceTypeEnum::d6:
		//
		break;

	case DiceTypeEnum::d4:
		//
		break;

	}
}



// Called every frame
void ADiceCube_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(UKismetMathLibrary::NearlyEqual_FloatFloat(this->GetVelocity().Length(),0,0.000001) && bIsBeenThrown)
	{
		DiceStoped();
	}
	if (bIsGrabbed)
	{
		FHitResult CursorHit;
		GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), false, CursorHit);
		this->SetActorLocation(FVector(CursorHit.Location.X, CursorHit.Location.Y, 550));
		//delay )
		if (TimeDelay >= 0.1f)
		{
			TimeDelay = 0.f;
			XDelayLocation = CursorHit.Location.X;
			YDelayLocation = CursorHit.Location.Y;
		}
		else
		{
			TimeDelay = TimeDelay + DeltaTime;
		}
	}
}

void ADiceCube_Base::DiceD20init()
{
	int16 number = 0;
	TArray<FVector> arr;
	FVector Location;
	FRotator Rotation;
	FVector CurrentLocation = this->GetActorLocation();
	FTransform ArrowTransf;
	FTransform RenderTransf;
	for (const FVector& Element : D20Normals)
	{
		Location = Element * DiceSize;
		Rotation = UKismetMathLibrary::FindLookAtRotation(CurrentLocation, Element * 1000 + CurrentLocation);
		RenderTransf.SetLocation(Location);
		RenderTransf.SetRotation(Rotation.Quaternion());
		RenderTransf.SetScale3D(FVector(0, 0, 0));
		ArrowTransf.SetLocation(Location);
		ArrowTransf.SetRotation(Rotation.Quaternion());
		ArrowTransf.SetScale3D(FVector(1, 1, 1));
		//TextRender
		UTextRenderComponent* NewRenderText = NewObject<UTextRenderComponent>(this); //в конструкторе NewObject нельзя
		//UTextRenderComponent* NewRenderText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender"));
		NewRenderText->SetRelativeTransform(RenderTransf);
		NewRenderText->SetText(FText::AsNumber(number));
		NewRenderText->SetWorldSize(40);
		NewRenderText->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
		NewRenderText->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
		NewRenderText->RegisterComponent(); //т.к. NewObject заменили на CreateDefaultSubobject
		TextRenders.Add(NewRenderText);
		//Arrow
		UArrowComponent* NewArrow = NewObject<UArrowComponent>(this); //в конструкторе NewObject нельзя
		//UArrowComponent* NewArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
		NewArrow->SetRelativeTransform(ArrowTransf);
		NewArrow->SetArrowSize(1);
		NewArrow->SetArrowLength(100);
		NewArrow->RegisterComponent(); //т.к. NewObject заменили на CreateDefaultSubobject
		Normals.Add(NewArrow);
	}
}

void ADiceCube_Base::DiceStoped()
{

}

const TArray<FVector> ADiceCube_Base::D20Normals =
{
	TArray<FVector>{
		FVector(0.577,0.333,0.745), FVector(0.577,0.745,-0.333), FVector(0.577,-0.745,0.333), FVector(0.577,-0.333,-0.745), 
		FVector(-0.577,0.333,0.745), FVector(-0.577,0.745,-0.333), FVector(-0.577,-0.745,0.333), FVector(-0.577,-0.333,-0.745), 
		FVector(0,0,1), FVector(0,0.667,-0.745), FVector(0,-0.667,0.745), FVector(0,0,-1), 
		FVector(0.357,0.873,0.333), FVector(0.357,-0.873,-0.333), FVector(-0.357,0.873,0.333), FVector(-0.357,-0.873,-0.333), 
		FVector(0.934,-0.127,0.333), FVector(0.934,0.127,-0.333), FVector(-0.934,-0.127,0.333), FVector(-0.934,0.127,-0.333)
	}
};