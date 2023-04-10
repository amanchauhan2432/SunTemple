// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class SUNTEMPLE_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

	UPROPERTY(EditAnywhere)
	class UBoxComponent* SpawningBox;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACritter> SpawningActor;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* SpawnEffect = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector GetSpawnLocation();

};
