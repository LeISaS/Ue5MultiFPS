// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PlayerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API APlayerGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	virtual void PlayerEliminated(class APlayerCharacter* ElimmedCharacter, class APlayerCharacterController* VictimController, APlayerCharacterController* AttackerController);
	virtual void RequestRespawn(ACharacter* ElimmedCharacter, AController* ElimmedController);
};
