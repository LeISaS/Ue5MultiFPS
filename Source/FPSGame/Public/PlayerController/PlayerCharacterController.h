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
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void SetHUDTime();
private:

	class APlayerHUD* PlayerHUD;

	float MatchTime = 120.f;
	uint32 CountdownInt = 0;
};
