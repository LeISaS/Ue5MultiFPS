// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/PlayerCharacterState.h"
#include "Character/PlayerCharacter.h"
#include "PlayerController/PlayerCharacterController.h"
#include "Net/UnrealNetwork.h"
void APlayerCharacterState::OnRep_Score()
{
	Super::OnRep_Score();

	Character = Character == nullptr ? Cast<APlayerCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<APlayerCharacterController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDScore(GetScore());
		}
	}
}



void APlayerCharacterState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerCharacterState, Deaths);
}

void APlayerCharacterState::AddToScore(float ScoreAmount)
{
	SetScore(GetScore() + ScoreAmount);

	Character = Character == nullptr ? Cast<APlayerCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<APlayerCharacterController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDScore(GetScore());

		}
	}
}

void APlayerCharacterState::OnRep_Deaths()
{
	Character = Character == nullptr ? Cast<APlayerCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<APlayerCharacterController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDDeath(Deaths);

		}
	}
}

void APlayerCharacterState::AddToDeaths(int32 DeathsCount)
{
	Deaths +=DeathsCount;

	Character = Character == nullptr ? Cast<APlayerCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<APlayerCharacterController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDDeath(Deaths);

		}
	}
}
