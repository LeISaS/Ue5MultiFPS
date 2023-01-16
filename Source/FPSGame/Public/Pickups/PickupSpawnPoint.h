// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupSpawnPoint.generated.h"

UENUM(BlueprintType)
enum class ESpawnState : uint8
{
	ESS_Pickup		UMETA(DisplayName = "Pickup"),
	ESS_Weapon		UMETA(DisplayName = "Weapon"),

	ESS_Max		UMETA(DisplayName = "Max")
};

UCLASS()
class FPSGAME_API APickupSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	APickupSpawnPoint();

	UPROPERTY(EditAnywhere)
	ESpawnState SpawnState;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "SpawnState == ESpawnState::ESS_Pickup"))
	TArray<TSubclassOf<class APickup>> PickupClasses;

	UPROPERTY()
	APickup* SpawnedPickup;

	void SpawnPickup();
	void SpawnPickupTimerFinished();
	UFUNCTION()
	void StartSpawnPickupTimer(AActor* DestroyedActor);


	void SpawnWeaponPickup();

	UPROPERTY(EditAnywhere, meta = (EditCondition = "SpawnState == ESpawnState::ESS_Weapon"))
		TArray<TSubclassOf<class AWeapon>> WeaponClasses;

	UPROPERTY()
		AWeapon* SpawnedWeapon;


private:
	FTimerHandle SpawnPickupTimer;

	UPROPERTY(EditAnywhere)
	float SpawnPickupTimeMin;
	UPROPERTY(EditAnywhere)
	float SpawnPickupTimeMax;
public:	
	virtual void Tick(float DeltaTime) override;

};
