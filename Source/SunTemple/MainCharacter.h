// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class SUNTEMPLE_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float Health;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float MaxStamina = 200.f;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	int32 Coins = 0;

	bool bIsSprinting = false;

	bool bCanEquip = false;

	UPROPERTY(EditAnywhere)
	class AWeapon* EquippedWeapon;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Forward(float AxisValue);
	void Right(float AxisValue);

	void Sprint();
	void StopSprint();

	UFUNCTION(BlueprintCallable)
	float GetHealthPercent();

	UFUNCTION(BlueprintCallable)
	float GetStaminaPercent();

	UFUNCTION(BlueprintCallable)
	bool IsDead() const;

	FORCEINLINE void SetWeapon(AWeapon* WeaponToSet) {EquippedWeapon = WeaponToSet;}

	void KeyDown();
	void KeyUp();

};
