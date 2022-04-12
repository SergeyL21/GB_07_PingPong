// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PingPongGameModeBase.generated.h"

class APingPongPlayerController;
class APlayerStart;
/**
 * 
 */
UCLASS()
class PINGPONG_API APingPongGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
    UPROPERTY()
    APingPongPlayerController* Player1;
	
    UPROPERTY()
    APingPongPlayerController* Player2;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    APlayerStart* Player1Start;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    APlayerStart* Player2Start;

	UPROPERTY()
	int32 Player1Score { 0 };

	UPROPERTY()
	int32 Player2Score { 0 };
	
public:
    APingPongGameModeBase();
	
    virtual void BeginPlay() override;
	
    virtual void PostLogin(APlayerController* NewPlayer) override;

	void PlayerGoal(int32 PlayerID);
};
