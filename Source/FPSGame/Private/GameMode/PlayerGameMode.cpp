// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PlayerGameMode.h"
#include "Character/PlayerCharacter.h"
#include "PlayerController/PlayerCharacterController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "PlayerState/PlayerCharacterState.h"
#include "GameState/PlayerGameState.h"

namespace MatchState
{
	const FName Cooldown = FName("Cooldown");
}

APlayerGameMode::APlayerGameMode()
{
	bDelayedStart = true;
}

void APlayerGameMode::BeginPlay()
{
	Super::BeginPlay();
	LevelStartingTime = GetWorld()->GetTimeSeconds();
}

void APlayerGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MatchState == MatchState::WaitingToStart)
	{
		CountdownTime = WarmupTime - GetWorld()->GetTimeSeconds()+LevelStartingTime;
		if (CountdownTime <= 0.f)
		{
			StartMatch();
		}
	}
	else if (MatchState == MatchState::InProgress)
	{
		CountdownTime = WarmupTime + MatchTime - GetWorld()->GetTimeSeconds() + LevelStartingTime;
		if (CountdownTime <= 0.f)
		{
			SetMatchState(MatchState::Cooldown);
		}
	}
	else if (MatchState == MatchState::Cooldown)
	{
		CountdownTime = CooldownTime + WarmupTime + MatchTime - GetWorld()->GetTimeSeconds() + LevelStartingTime;
		if (CountdownTime <= 0.f)
		{
			RestartGame();
		}
	}
}

void APlayerGameMode::OnMatchStateSet()
{
	Super::OnMatchStateSet();

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerCharacterController* PlayerCharacter = Cast<APlayerCharacterController>(*It);
		if (PlayerCharacter)
		{
			PlayerCharacter->OnMatchStateSet(MatchState);
		}
	}
}

void APlayerGameMode::PlayerEliminated(class APlayerCharacter* ElimmedCharacter, APlayerCharacterController* VictimController, APlayerCharacterController* AttackerController)
{
	if (AttackerController == nullptr || AttackerController->PlayerState == nullptr) return;
	if (VictimController == nullptr || VictimController->PlayerState == nullptr) return;

	APlayerCharacterState* AttackerPlayerState = AttackerController ? Cast<APlayerCharacterState>(AttackerController->PlayerState) : nullptr;
	APlayerCharacterState* VictimPlayerState = VictimController ? Cast<APlayerCharacterState>(VictimController->PlayerState) : nullptr;

	APlayerGameState* PlayerGameState = GetGameState < APlayerGameState>();

	if (AttackerPlayerState && AttackerPlayerState != VictimPlayerState)
	{
		AttackerPlayerState->AddToScore(1.f);

		PlayerGameState->UpdateTopScore(AttackerPlayerState);

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
