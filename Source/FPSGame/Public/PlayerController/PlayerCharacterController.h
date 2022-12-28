// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void SetHUDHealth(float Health, float MaxHealth);
	void SetHUDScore(float Score);
	void SetHUDDeath(int32 DeathCount);
	void SetWeaponAmmo(int32 Ammo);
	void SetCarriedAmmo(int32 Ammo);
	void SetMatchCountdown(float  CountdownTime);
	virtual void OnPossess(APawn* InPawn) override;

	virtual float GetServerTime();
	virtual void ReceivedPlayer() override;
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void SetHUDTime();


	UFUNCTION(Server, Reliable)
		void ServerRequestServerTime(float TimeOfClientRequest);

	UFUNCTION(Client, Reliable)
		void ClientReportServerTime(float TimeOfClientRequest, float TimeServerReceivedClientRequest);

	float ClientServerDelta = 0.f;

	UPROPERTY(EditAnywhere, Category = Time)
	float TimeSyncFrequency = 5.f;

	float TimeSyncRunningTime = 0.f;
	void CheckTimeSync(float DeltaTime);
private:

	class APlayerHUD* PlayerHUD;

	float MatchTime = 120.f;
	uint32 CountdownInt = 0;
};
