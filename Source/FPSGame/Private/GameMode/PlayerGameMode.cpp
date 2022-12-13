// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PlayerGameMode.h"
#include "Character/PlayerCharacter.h"
#include "PlayerController/PlayerCharacterController.h"

void APlayerGameMode::PlayerEliminated(class APlayerCharacter* ElimmedCharacter, APlayerCharacterController* VictimController, APlayerCharacterController* AttackerController)
{
	if (ElimmedCharacter)
	{
		ElimmedCharacter->Elim();
	}
}
