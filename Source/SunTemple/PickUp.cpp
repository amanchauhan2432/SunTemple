// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp.h"
#include "MainCharacter.h"

APickUp::APickUp()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void APickUp::BeginPlay()
{
    Super::BeginPlay();

    Player = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void APickUp::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APickUp::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

    Player->Coins++;
    
    Destroy();
}
