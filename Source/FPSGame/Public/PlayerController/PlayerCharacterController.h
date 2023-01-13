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
	void SetHUDShield(float Shield, float MaxShield);
	void SetHUDScore(float Score);
	void SetHUDDeath(int32 DeathCount);
	void SetWeaponAmmo(int32 Ammo);
	void SetCarriedAmmo(int32 Ammo);
	void SetMatchCountdown(float  CountdownTime);
	void SetHUDAnnouncemnetCountdown(float CountdownTime);
	void SetHUDGrenades(int32 Grenades);
	virtual void OnPossess(APawn* InPawn) override;

	virtual float GetServerTime();
	virtual void ReceivedPlayer() override;
	void OnMatchStateSet(FName State);
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void HandleMatchHasStarted();
	void HandleCooldown();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void SetHUDTime();

	void PoollInit();

	UFUNCTION(Server, Reliable)
		void ServerRequestServerTime(float TimeOfClientRequest);

	UFUNCTION(Client, Reliable)
		void ClientReportServerTime(float TimeOfClientRequest, float TimeServerReceivedClientRequest);

	float ClientServerDelta = 0.f;

	UPROPERTY(EditAnywhere, Category = Time)
	float TimeSyncFrequency = 5.f;

	float TimeSyncRunningTime = 0.f;
	void CheckTimeSync(float DeltaTime);

	UFUNCTION(Server, Reliable)
	void ServerCheckMatchState();

	UFUNCTION(Client,Reliable)
	void ClientJoinMidgame(FName StateOfMatch, float Warmup, float Match, float Cooldown,float StartingTime);
private:
	UPROPERTY()
	class APlayerHUD* PlayerHUD;

	UPROPERTY()
	class APlayerGameMode* PlayerGameMode;

	float LevelStartingTime = 0.f;
	float MatchTime = 0.f;
	float WarmupTime = 0.f;
	float CooldownTime = 0.f;
	uint32 CountdownInt = 0;

	UPROPERTY(ReplicatedUsing = OnRep_MatchState)
	FName MatchState;

	UFUNCTION()
	void OnRep_MatchState();

	UPROPERTY()
	class UCharacterOverlay* CharacterOverlay;


	float HUDHealth;
	float HUDMaxHealth;
	bool bInitializeHealth = false;

	float HUDScore;
	bool bInitializeScore = false;

	int32 HUDDefeats;
	bool bInitializeDefeats = false;

	int32 HUDGrenades;
	bool bInitializeGrenades = false;

	float HUDShield;
	float HUDMaxShield;
	bool bInitializeShield = false;
};
