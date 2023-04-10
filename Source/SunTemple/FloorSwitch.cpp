// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorSwitch.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFloorSwitch::AFloorSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = TriggerBox;

	FloorSwitch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Switch"));
	FloorSwitch->SetupAttachment(RootComponent);

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFloorSwitch::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFloorSwitch::OnBeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AFloorSwitch::OnEndOverlap);
	
	InitialDoorLocation = Door->GetComponentLocation();
	InitialSwitchLocation = FloorSwitch->GetComponentLocation();
}

// Called every frame
void AFloorSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloorSwitch::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Begin Overlap."));
	OpenDoor();
	OpenSwitch();
	bIsCharacterOnSwitch = true;
}

void AFloorSwitch::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("End Overlap."));
	bIsCharacterOnSwitch =false;

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AFloorSwitch::CloseDelay, 2.f);
}

void AFloorSwitch::UpdateDoorLocation(float Z)
{
	FVector Current = InitialDoorLocation;
	Current.Z += Z;
	Door->SetWorldLocation(Current);
}

void AFloorSwitch::UpdateSwitchLocation(float Z)
{
	FVector Current = InitialSwitchLocation;
	Current.Z += Z;
	FloorSwitch->SetWorldLocation(Current);
}

void AFloorSwitch::CloseDelay()
{
	if (!bIsCharacterOnSwitch)
	{
		CloseDoor();
		CloseSwitch();
	}
}