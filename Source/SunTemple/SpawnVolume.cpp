// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Critter.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SpawningBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
	if (!SpawningActor || !SpawnEffect) { return ;}
	FActorSpawnParameters SpawnParams;
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(GetSpawnLocation());
	GetWorld()->SpawnActor<ACritter>(SpawningActor, SpawnTransform, SpawnParams);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SpawnEffect, SpawnTransform);
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnVolume::GetSpawnLocation()
{
	FVector BoxOrigin = SpawningBox->GetComponentLocation();
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();

	return UKismetMathLibrary::RandomPointInBoundingBox(BoxOrigin, BoxExtent);
}

