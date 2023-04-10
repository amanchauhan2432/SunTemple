// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class SUNTEMPLE_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	UPROPERTY(EditAnywhere, Category = "Item")
	class USphereComponent* CollisionVolume;

	UPROPERTY(EditAnywhere, Category = "Item")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Item")
	class UParticleSystemComponent* IdleParticle;

	UPROPERTY(EditAnywhere, Category = "Item")
	class UParticleSystem* OverlapParticle = nullptr;

	UPROPERTY(EditAnywhere, Category = "Item")
	class USoundBase* OverlapSound = nullptr;

	UPROPERTY(EditAnywhere, Category = "Item")
	bool bRotate = true;

	UPROPERTY(EditAnywhere, Category = "Item")
	float RotationSpeed = 45.f;

	float RunningTime = 0.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
