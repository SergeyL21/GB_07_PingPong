// Copyright Epic Games, Inc. All Rights Reserved.

#include "PingPongGameModeBase.h"

#include "PingPongGate.h"
#include "PingPongPlayerController.h"
#include "PingPongPlayerPawn.h"

#include "GameFramework/PlayerStart.h"
#include "EngineUtils.h"

// --------------------------------------------------------------------------------------
namespace utils
{
	template<typename T>
	void FindAllActors(UWorld* World, TArray<T*>& Out)
	{
		for (TActorIterator<T> It(World); It; ++It)
		{
			Out.Add(*It);
		}
	}
} // namespace utils

// --------------------------------------------------------------------------------------
APingPongGameModeBase::APingPongGameModeBase()
{
	DefaultPawnClass = APingPongPlayerPawn::StaticClass();
	PlayerControllerClass = APingPongPlayerController::StaticClass();
}

// --------------------------------------------------------------------------------------
void APingPongGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

// --------------------------------------------------------------------------------------
void APingPongGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	UWorld* World { GetWorld() };
	if(World && (!Player1Start || !Player2Start))
	{
		TArray<APlayerStart*> FoundActors;
		utils::FindAllActors<APlayerStart>(World, FoundActors);
		if(FoundActors.Num() > 0)
		{
			Player1Start = FoundActors[0];
		}
		if(FoundActors.Num() > 1)
		{
			Player2Start = FoundActors[1];
		}
	}
	APingPongPlayerController* CurrPlayer;
	APlayerStart* StartPos;
	int32 PlayerID;
	
	if (Player1 == nullptr)
	{
		Player1 = Cast<APingPongPlayerController>(NewPlayer);
		PlayerID = 1;
		CurrPlayer = Player1;
		StartPos = Player1Start;
		UE_LOG(LogTemp, Warning, TEXT("PingPongGameMode: Init player 1"));
	}
	else if (Player2 == nullptr)
	{
		Player2 = Cast<APingPongPlayerController>(NewPlayer);
		PlayerID = 2;
		CurrPlayer = Player2;
		StartPos = Player2Start;
		UE_LOG(LogTemp, Warning, TEXT("PingPongGameMode: Init player 2"));
	}
	else
	{
		UE_LOG(LogTemp, Error,
			TEXT("PingPongGameMode: There are already two players in the game. New connections are not possible"));
		return;
	}
	
	APingPongPlayerPawn* newPawn { Cast<APingPongPlayerPawn>(NewPlayer->GetPawn()) };
	if (!newPawn)
	{
		newPawn = World->SpawnActor<APingPongPlayerPawn>(DefaultPawnClass);
	}

	TArray<APingPongGate*> FoundGateActors;
	utils::FindAllActors<APingPongGate>(World, FoundGateActors);
	auto FindGateByPlayerStart = [](const TArray<APingPongGate*>& Array, const APlayerStart* SearchObject)
	{
		auto Result = Array.FindByPredicate([&](const APingPongGate *Gate)
		{
			return Gate->PlayerStart == SearchObject;
		});
		return Result != nullptr ? *Result : nullptr;
	};
	
	if (newPawn)
	{
		auto PlayerGate { FindGateByPlayerStart(FoundGateActors, StartPos) }; 
		newPawn->SetActorLocation(StartPos->GetActorLocation());
		newPawn->SetActorRotation(StartPos->GetActorRotation());
		NewPlayer->SetPawn(newPawn);
		CurrPlayer->SetStartTransform(StartPos->GetActorTransform());
		CurrPlayer->Client_InitializeHUD();
		CurrPlayer->Server_Initialize(PlayerID, PlayerGate);
	}
	else
    {
	    UE_LOG(LogTemp, Error, TEXT("Start position not setted in PingPongGameMode!"));
    }
}

// --------------------------------------------------------------------------------------
void APingPongGameModeBase::PlayerGoal(int32 PlayerID)
{
	auto CurrentPlayerScore { 0 };
	if (PlayerID == 1)
	{
		CurrentPlayerScore = ++Player2Score;
	}
	else if (PlayerID == 2)
	{
		CurrentPlayerScore = ++Player1Score;
	}
	
	for (auto Iterator {GetWorld()->GetPlayerControllerIterator()}; Iterator; ++Iterator)
	{
		auto PlayerController { Cast<APingPongPlayerController>(*Iterator) };
		if (PlayerController != nullptr)
		{
			if (PlayerController->GetPlayerID() == PlayerID)
			{
				PlayerController->UpdateWidgetEnemyScore(CurrentPlayerScore);
			}
			else
			{
				PlayerController->UpdateWidgetPlayerScore(CurrentPlayerScore);
			}
		}
	}
}


