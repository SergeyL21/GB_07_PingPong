// Fill out your copyright notice in the Description page of Project Settings.

#include "PingPongPlayerController.h"

#include "PingPongGate.h"
#include "PingPongPlatform.h"
#include "PlayerWidget.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/HUD.h"
#include "Net/UnrealNetwork.h"

// --------------------------------------------------------------------------------------
APingPongPlayerController::APingPongPlayerController()
{
	SetReplicates(true);
}

// --------------------------------------------------------------------------------------
void APingPongPlayerController::SetStartTransform(const FTransform& NewStartTransform)
{
	StartTransform = NewStartTransform;
}

// --------------------------------------------------------------------------------------
void APingPongPlayerController::SetPlatformSkin(FSoftObjectPath SkinMaterialAsset)
{
	Server_SetPlatformSkin(SkinMaterialAsset);
}

// --------------------------------------------------------------------------------------
void APingPongPlayerController::SetGateSkin(FSoftObjectPath SkinMaterialAsset)
{
	Server_SetGateSkin(SkinMaterialAsset);
}

// --------------------------------------------------------------------------------------
void APingPongPlayerController::Client_SetHUDWindow_Implementation(PlayerWindowId windowId)
{
	if (Widget)
	{
		Widget->SwitchWidget(static_cast<int32>(windowId));
	}
}

// --------------------------------------------------------------------------------------
void APingPongPlayerController::Server_Initialize_Implementation(int32 NewPlayerID, APingPongGate* NewGate)
{
	if (Platform)
	{
		Platform->Destroy();
	}
	SpawnPlatform(PlatformClass);

	PlayerID = NewPlayerID;
	Gate = NewGate;
	Gate->SetPlayerID(PlayerID);
}

// --------------------------------------------------------------------------------------
bool APingPongPlayerController::Server_Initialize_Validate(int32 NewPlayerID, APingPongGate* NewGate)
{
	return (NewPlayerID != 0 && NewGate != nullptr);
}

// --------------------------------------------------------------------------------------
void APingPongPlayerController::Client_InitializeHUD_Implementation()
{
	if (!Widget)
	{
		Widget = CreateWidget<UPlayerWidget>(this, WidgetClass);
		if (Widget)
		{
			Widget->UpdatePlayerScore(0);
			Widget->UpdateEnemyScore(0);
			Widget->AddToViewport();
		}
	}
}

// --------------------------------------------------------------------------------------
bool APingPongPlayerController::Client_InitializeHUD_Validate()
{
	return (WidgetClass != nullptr);
}

// --------------------------------------------------------------------------------------
void APingPongPlayerController::SpawnPlatform_Implementation(TSubclassOf<APingPongPlatform> InPlatformClass)
{
	Platform = GetWorld()->SpawnActor<APingPongPlatform>(InPlatformClass);
    if (Platform)
    {
		Platform->SetActorLocation(StartTransform.GetLocation());
		Platform->SetActorRotation(StartTransform.GetRotation());
    }
}

// --------------------------------------------------------------------------------------
bool APingPongPlayerController::SpawnPlatform_Validate(TSubclassOf<APingPongPlatform> InPlatformClass)
{
	return InPlatformClass != nullptr;
}

// --------------------------------------------------------------------------------------
void APingPongPlayerController::UpdateWidgetPlayerScore_Implementation(int32 Score)
{
	Widget->UpdatePlayerScore(Score);
}

// --------------------------------------------------------------------------------------
void APingPongPlayerController::UpdateWidgetEnemyScore_Implementation(int32 Score)
{
	Widget->UpdateEnemyScore(Score);
}

// --------------------------------------------------------------------------------------
void APingPongPlayerController::Server_SetPlatformSkin_Implementation(FSoftObjectPath SkinMaterialAsset)
{
	if (SkinMaterialAsset.IsValid())
	{
		auto SkinMaterial { Cast<UMaterial>(SkinMaterialAsset.TryLoad()) };
		if (SkinMaterial && Platform)
		{
			Platform->SetSkin(SkinMaterial);
		}
	}
}

// --------------------------------------------------------------------------------------
void APingPongPlayerController::Server_SetGateSkin_Implementation(FSoftObjectPath SkinMaterialAsset)
{
	if (SkinMaterialAsset.IsValid())
	{
		auto SkinMaterial { Cast<UMaterial>(SkinMaterialAsset.TryLoad()) };
		if (SkinMaterial && Gate)
		{
			Gate->SetSkin(SkinMaterial);
		}
	}
}

// --------------------------------------------------------------------------------------
void APingPongPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAxis("Move", this, &APingPongPlayerController::MoveRight);
}

// --------------------------------------------------------------------------------------
void APingPongPlayerController::MoveRight(float AxisValue)
{
	if (AxisValue != 0)
    {
		UE_LOG(LogTemp, Warning, TEXT("APingPongPlayerController::MoveRight"));
    }
    Server_PlatformMoveRight(AxisValue);
}

// --------------------------------------------------------------------------------------
void APingPongPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(APingPongPlayerController, PlayerID, COND_SimulatedOnly);
}

// --------------------------------------------------------------------------------------
void APingPongPlayerController::Server_PlatformMoveRight_Implementation(float AxisValue)
{
	if (Platform)
	{
		if (AxisValue != 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("APingPongPlayerController::Server_PlatformMoveRight_Implementation"));
		}
		Platform->Server_MoveRight(AxisValue);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("APingPongPlayerController::Server_PlatformMoveRight_Implementation: HAS NO PLATFORM!"));
	}
}

// --------------------------------------------------------------------------------------
bool APingPongPlayerController::Server_PlatformMoveRight_Validate(float AxisValue)
{
	return true;
}

