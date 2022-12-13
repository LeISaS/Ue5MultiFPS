// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerCharacterState.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API APlayerCharacterState : public APlayerState
{
	GENERATED_BODY()
	
public:
	virtual void OnRep_Score() override;
	UFUNCTION()
	virtual void OnRep_Deaths();
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
	void AddToScore(float ScoreAmount);
	void AddToDeaths(int32 DeathsCount);
private:
	UPROPERTY()
	class APlayerCharacter* Character;
	UPROPERTY()
	class APlayerCharacterController* Controller;

	UPROPERTY(ReplicatedUsing = OnRep_Deaths)
	int32 Deaths;



};
