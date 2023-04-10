// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "MainCharacter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "MainCharacter.h"

AWeapon::AWeapon()
{
    SMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SMesh"));
    SMesh->SetupAttachment(RootComponent);   
}

void AWeapon::BeginPlay()
{
    Super::BeginPlay();

}

void AWeapon::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);


    AMainCharacter* Player = Cast<AMainCharacter>(OtherActor);
    UE_LOG(LogTemp, Warning, TEXT("Value : %d"), Player->bCanEquip);

    if (Player)
    {
        Player->SetWeapon(this);
    }
}

void AWeapon::Equip(AMainCharacter* Player)
{
    if (Player)
    {
        SMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
        SMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

        SMesh->SetSimulatePhysics(false);
        const USkeletalMeshSocket* Socket = Player->GetMesh()->GetSocketByName(TEXT("WeaponSocket"));
        Socket->AttachActor(this, Player->GetMesh());

        bRotate = false;
    }
}
