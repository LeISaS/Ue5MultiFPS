// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PlayerGameMode.h"
#include "Character/PlayerCharacter.h"
#include "PlayerController/PlayerCharacterController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "PlayerState/PlayerCharacterState.h"
void APlayerGameMode::PlayerEliminated(class APlayerCharacter* ElimmedCharacter, APlayerCharacterController* VictimController, APlayerCharacterController* AttackerController)
{
	APlayerCharacterState* AttackerPlayerState = AttackerController ? Cast<APlayerCharacterState>(AttackerController->PlayerState) : nullptr;
	APlayerCharacterState* VictimPlayerState = VictimController ? Cast<APlayerCharacterState>(VictimController->PlayerState) : nullptr;

	if (AttackerPlayerState && AttackerPlayerState != VictimPlayerState)
	{
		AttackerPlayerState->AddToScore(1.f);
	}
	if (VictimPlayerState)
	{
		VictimPlayerState->AddToDeaths(1);
	}

	if (ElimmedCharacter)
	{
		ElimmedCharacter->Elim();
	}
}

void APlayerGameMode::RequestRespawn(ACharacter* ElimmedCharacter, AController* ElimmedController)
{
	if (ElimmedCharacter)
	{
		ElimmedCharacter->Reset();
		ElimmedCharacter->Destroy();
	}
	if (ElimmedController)
	{
		TArray<AActor*> PlayerStarts;
		UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), PlayerStarts);
		int32 Selection = FMath::RandRange(0, PlayerStarts.Num() - 1);
		RestartPlayerAtPlayerStart(ElimmedController, PlayerStarts[Selection]);
	}
}
