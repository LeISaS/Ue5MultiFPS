// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"
void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();

	if (NumberOfPlayers == 1)
	{
		if (GetWorld())
		{
			bUseSeamlessTravel = true;
			GetWorld()->ServerTravel(FString("/Game/Maps/StageMasterMap?listen"));
		}
	}
}