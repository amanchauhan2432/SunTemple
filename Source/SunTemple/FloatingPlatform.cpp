// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingPlatform.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFloatingPlatform::AFloatingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

}

// Called when the game starts or when spawned
void AFloatingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	StartPoint = GetActorLocation();
	EndPoint += StartPoint;

	GetWorldTimerManager().SetTimer(MoveTimer, this, &AFloatingPlatform::Toggle, 2.f, true);
}

// Called every frame
void AFloatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsUp)
	{
		Current = GetActorLocation();
		Current = FMath::VInterpTo(Current, EndPoint, DeltaTime, Speed);
		SetActorLocation(Current);
	}
	else
	{
		Current = GetActorLocation();
		Current = FMath::VInterpTo(Current, StartPoint, DeltaTime, Speed);
		SetActorLocation(Current);
	}
}

void AFloatingPlatform::Toggle()
{
	bIsUp = !bIsUp;
}