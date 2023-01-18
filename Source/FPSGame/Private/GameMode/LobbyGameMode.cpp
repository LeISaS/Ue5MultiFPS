// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"
ALobbyGameMode::ALobbyGameMode() 
{
	LevelName.Add(FString("/Game/Maps/dm_rampCutter?listen"));
	LevelName.Add(FString("/Game/Maps/dm_noseBleeder?listen"));
	LevelName.Add(FString("/Game/Maps/dm_cubeRunner?listen"));
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
	int32 LevelNameCount = FMath::RandRange(0, LevelName.Num());

	if (NumberOfPlayers == 2)
	{
		if (GetWorld())
		{
			bUseSeamlessTravel = true;
			GetWorld()->ServerTravel(LevelName[LevelNameCount]);
		}
	}
}
