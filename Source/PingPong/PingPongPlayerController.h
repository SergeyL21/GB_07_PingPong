// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PingPongPlayerController.generated.h"

class APingPongPlatform;
class APingPongGate;
class UPlayerWidget;
/**
 * 
 */
UCLASS()
class PINGPONG_API APingPongPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	FTransform StartTransform;

	UPROPERTY(Replicated)
	int32 PlayerID { 0 };
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<APingPongPlatform> PlatformClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	APingPongPlatform* Platform;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	APingPongGate* Gate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> WidgetClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UPlayerWidget* Widget;

public:
	APingPongPlayerController();
	
	UFUNCTION()
	void SetStartTransform(const FTransform &NewStartTransform);

	UFUNCTION()
	FORCEINLINE int32 GetPlayerID() const { return PlayerID; }
	
	UFUNCTION(Client, Reliable, WithValidation)
	void Client_InitializeHUD();
	
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Initialize(int32 NewPlayerID, APingPongGate* NewGate);
	
	UFUNCTION(Server, Reliable, WithValidation)
	void SpawnPlatform(TSubclassOf<APingPongPlatform> InPlatformClass);
	
	UFUNCTION(Client, Reliable)
	void UpdateWidgetPlayerScore(int32 Score);

	UFUNCTION(Client, Reliable)
	void UpdateWidgetEnemyScore(int32 Score);
	
	virtual void SetupInputComponent() override;

protected:
	UFUNCTION()
	void MoveRight(float AxisValue);
	
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_PlatformMoveRight(float AxisValue);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
