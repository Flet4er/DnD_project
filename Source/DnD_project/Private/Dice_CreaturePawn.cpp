// Copyright (c) Blizickij Vladimir. All rights reserved


#include "Dice_CreaturePawn.h"
#include "MyAttributeSet.h"
#include "HealthBoost.h"
#include "GA_Fireball.h"
#include "GameplayAbilitySet.h"
#include "AbilitySystemBlueprintLibrary.h"



// Sets default values
ADice_CreaturePawn::ADice_CreaturePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetReplicates(true);
	SetReplicateMovement(true);

	RootSceneComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
	SetRootComponent(RootSceneComponent);

	MyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("3DModels"));
	MyMeshComponent->SetupAttachment(RootSceneComponent);
	MyMeshComponent->OnClicked.AddDynamic(this, &ADice_CreaturePawn::OnMeshClicked);
	MyMeshComponent->OnReleased.AddDynamic(this, &ADice_CreaturePawn::OnMeshReleased);
	//GAS
	ASComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComp"));
	ASComponent->SetIsReplicated(true);
	ASComponent->ReplicationMode = EGameplayEffectReplicationMode::Mixed;
	AttributeSet = CreateDefaultSubobject<UMyAttributeSet>(TEXT("AttributeSet"));
	ASComponent->AddAttributeSetSubobject(AttributeSet);

}

// Called when the game starts or when spawned
void ADice_CreaturePawn::BeginPlay()
{
	Super::BeginPlay();

	ASComponent->InitAbilityActorInfo(this, this); //если оставить в конструкторе - краш
	PawnOwner = Cast<APlayerController>(GetOwner());
	AttributeSet->Health.SetCurrentValue(1000);
	AttributeSet->Health.SetBaseValue(1000);

	int32 HealAmount = 500;
	TSubclassOf<UGameplayEffect> EffectClass = UHealthBoost::StaticClass();
	FGameplayEffectContextHandle Context = ASComponent->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = ASComponent->MakeOutgoingSpec(UHealthBoost::StaticClass(), 1.0f, Context);

	// ”станавливаем значение дл€ SetByCaller
	SpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag("Attribute.Health"), HealAmount);
	//применение
	ASComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());


	if (ASComponent)
	{
		if (HasAuthority())
		{
			//ƒаем стартовые абилки
			TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
			StartupAbilities.Add(UGA_Fireball::StaticClass());

			for (auto Ability : StartupAbilities)
			{
				ASComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, 0));
			}
		}

		if (IsLocallyControlled())
		{
			SetupAbilityInput();
		}
	}

	TArray<AActor*> Targets;
	Targets.Add(this);

	// —оздаЄм EventData и дл€ ивента
	FGameplayAbilityTargetDataHandle TargetDataHandle =	UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActorArray(Targets, true);	
	FGameplayEventData EventData;
	EventData.Instigator = this;
	EventData.TargetData = TargetDataHandle;
	// ќтправл€ем EventData и тригерим ивент у класса с тегом "Event.CastWithTargets" 
	ASComponent->HandleGameplayEvent(FGameplayTag::RequestGameplayTag(FName("Event.CastWithTargets")), &EventData);

	// обычна€ активаци€, с такой нужно выбор цели делать внутри UGA_Fireball
	//ASComponent->TryActivateAbilityByClass(UGA_Fireball::StaticClass());
		
	int32 nub = AttributeSet->Health.GetCurrentValue();
	UE_LOG(LogTemp,Log, TEXT("CurrentHelath is %i"), nub)
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
			FVector Location = { HitResult.Location.X,HitResult.Location.Y, 50 }; // 50 - положение плоскости, пока захардкожено
			RootSceneComponent->SetWorldLocation(Location, false);
		}

		if (PawnOwner != nullptr && PawnOwner->GetLocalRole() == ROLE_AutonomousProxy)
		{
			PawnOwner->GetHitResultUnderCursorByChannel(TraceTypeQuery1, false, HitResult);
			FVector Location = { HitResult.Location.X,HitResult.Location.Y, 50 }; // 50 - положение плоскости, пока захардкожено
			//RootSceneComponent->SetWorldLocation(Location, false);
			SetLocation_server(Location);
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

void ADice_CreaturePawn::SetupAbilityInput()
{
	if (!ASComponent) return;

	TArray<FGameplayAbilityBindInfo> BindInfos;
	BindInfos.Add(FGameplayAbilityBindInfo(EGameplayAbilityInputBinds::Ability1, UGA_Fireball::StaticClass()));

	ASComponent->BindAbilityActivationToInputComponent(
		InputComponent,
		FGameplayAbilityInputBinds(
			TEXT("ConfirmTarget"),
			TEXT("CancelTarget"),
			TEXT("EAbilityInputID"),
			static_cast<int32>(EAbilityInputID::None),
			static_cast<int32>(EAbilityInputID::Fireball)
		)
	);
}
void ADice_CreaturePawn::SetLocation_server_Implementation(FVector Location)
{
	FVector CurrentLocation = this->GetActorLocation();
	FVector VInterpLocation = FMath::VInterpTo(CurrentLocation, Location, GetWorld()->GetDeltaSeconds(), 50.f); 
	//FVector SetLocation = FMath::Lerp(CurrentLocation, Location, .5f);
	FVector SetLocation = { VInterpLocation.X,VInterpLocation.Y, 50 };
	this->RootSceneComponent->SetWorldLocation(SetLocation, false);
}

