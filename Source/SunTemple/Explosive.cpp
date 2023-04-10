// Fill out your copyright notice in the Description page of Project Settings.


#include "Explosive.h"
#include "MainCharacter.h"

AExplosive::AExplosive()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AExplosive::BeginPlay()
{
    Super::BeginPlay();

    Player = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void AExplosive::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void AExplosive::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
    
    Player->Health -= 10.f;
    
    Destroy();
}
