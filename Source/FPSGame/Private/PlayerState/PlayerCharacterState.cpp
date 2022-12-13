// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/PlayerCharacterState.h"
#include "Character/PlayerCharacter.h"
#include "PlayerController/PlayerCharacterController.h"
void APlayerCharacterState::OnRep_Score()
{
	Super::OnRep_Score();

	Character = Character == nullptr ? Cast<APlayerCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<APlayerCharacterController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDScore(Score);
		}
	}
}

void APlayerCharacterState::AddToScore(float ScoreAmount)
{
	Score += ScoreAmount;

	Character = Character == nullptr ? Cast<APlayerCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<APlayerCharacterController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDScore(Score);

		}
	}
}
