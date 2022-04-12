// Fill out your copyright notice in the Description page of Project Settings.

#include "PingPongGate.h"

#include "PingPongGameModeBase.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Net/UnrealNetwork.h"

// --------------------------------------------------------------------------------------
// Sets default values
APingPongGate::APingPongGate()
{
	PrimaryActorTick.bCanEverTick = true;
	BodyCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Gate BodyCollider"));
	SetRootComponent(BodyCollision);
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gate BodyMesh"));
	BodyMesh->SetupAttachment(RootComponent);
	BodyMesh->SetIsReplicated(true);
	SetReplicates(true);
}

// --------------------------------------------------------------------------------------
// Called when the game starts or when spawned
void APingPongGate::BeginPlay()
{
	Super::BeginPlay();
}

// --------------------------------------------------------------------------------------
void APingPongGate::Server_SetPlayerID_Implementation(int32 ID)
{
	PlayerID = ID;
}

// --------------------------------------------------------------------------------------
bool APingPongGate::Server_SetPlayerID_Validate(int32 ID)
{
	return ID != 0;
}

// --------------------------------------------------------------------------------------
// Called every frame
void APingPongGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// --------------------------------------------------------------------------------------
void APingPongGate::Server_Goal_Implementation()
{
	auto GameMode { Cast<APingPongGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())) };
	if (GameMode != nullptr)
	{
		GameMode->PlayerGoal(PlayerID);
	}
}

// --------------------------------------------------------------------------------------
bool APingPongGate::Server_Goal_Validate()
{
	return true;
}

// --------------------------------------------------------------------------------------
void APingPongGate::Goal()
{
	Server_Goal();
}

// --------------------------------------------------------------------------------------
void APingPongGate::SetPlayerID(int32 ID)
{
	Server_SetPlayerID(ID);
}

// --------------------------------------------------------------------------------------
void APingPongGate::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(APingPongGate, PlayerID, COND_SimulatedOnly);
}
