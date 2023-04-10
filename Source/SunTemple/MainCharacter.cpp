// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapon.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.f;
	SpringArm->SetRelativeLocation(FVector(0.f, 30.f, 60.f));
	SpringArm->SocketOffset = FVector(0.f, 30.f, 0.f);
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	bUseControllerRotationYaw = false; // Dont rotate the character with camera

	GetCharacterMovement()->MaxWalkSpeed = 250.f;
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character in the direction of movement.

	Health = MaxHealth;
	Stamina = MaxStamina;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Stamina < 10.f)
	{
		StopSprint();
	}
	if (bIsSprinting)
	{
		Stamina = FMath::Lerp(Stamina, 0.f, DeltaTime * 0.5f);
	}
	else
	{
		Stamina = FMath::Lerp(Stamina, MaxStamina, DeltaTime * 0.1f);
	}
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMainCharacter::Forward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMainCharacter::Right);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &AMainCharacter::Sprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &AMainCharacter::StopSprint);

	PlayerInputComponent->BindAction(TEXT("Equip"), IE_Pressed, this, &AMainCharacter::KeyDown);
	PlayerInputComponent->BindAction(TEXT("Equip"), IE_Released, this, &AMainCharacter::KeyUp);

}

void AMainCharacter::Forward(float AxisValue)
{
	const FRotator Rotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	const FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);

	AddMovementInput(Direction, AxisValue);
}

void AMainCharacter::Right(float AxisValue)
{
	const FRotator Rotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	const FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(Direction, AxisValue);
}

void AMainCharacter::Sprint()
{
	if (Stamina > 50.f)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.f;
		bIsSprinting = true;
	}	
}

void AMainCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 250.f;
	bIsSprinting = false;
}

float AMainCharacter::GetHealthPercent()
{
	return Health / MaxHealth;
}

float AMainCharacter::GetStaminaPercent()
{
	return Stamina / MaxStamina;
}

bool AMainCharacter::IsDead() const
{
	return Health <= 0.f;
}

void AMainCharacter::KeyDown()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->Equip(this);
	}
}

void AMainCharacter::KeyUp()
{
}