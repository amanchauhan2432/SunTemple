// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorSwitch.generated.h"

UCLASS()
class SUNTEMPLE_API AFloorSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorSwitch();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UBoxComponent* TriggerBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* FloorSwitch;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Door;

	FVector InitialDoorLocation;
	FVector InitialSwitchLocation;

	bool bIsCharacterOnSwitch = false;

	FTimerHandle TimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent)
	void OpenDoor();

	UFUNCTION(BlueprintImplementableEvent)
	void CloseDoor();

	UFUNCTION(BlueprintImplementableEvent)
	void OpenSwitch();

	UFUNCTION(BlueprintImplementableEvent)
	void CloseSwitch();

	UFUNCTION(BlueprintCallable)
	void UpdateDoorLocation(float Z);

	UFUNCTION(BlueprintCallable)
	void UpdateSwitchLocation(float Z);

	void CloseDelay();
};
