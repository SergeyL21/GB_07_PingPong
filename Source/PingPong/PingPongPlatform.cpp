// Fill out your copyright notice in the Description page of Project Settings.

#include "PingPongPlatform.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// --------------------------------------------------------------------------------------
APingPongPlatform::APingPongPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	BodyCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Platfrom BodyCollider"));
	SetRootComponent(BodyCollision);
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform BodyMesh"));
	BodyMesh->SetupAttachment(RootComponent);
	BodyMesh->SetIsReplicated(true);
	SetReplicates(true);
	SetReplicateMovement(true);
}

// --------------------------------------------------------------------------------------
void APingPongPlatform::BeginPlay()
{
	Super::BeginPlay();
}

// --------------------------------------------------------------------------------------
void APingPongPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// --------------------------------------------------------------------------------------
void APingPongPlatform::Server_MoveRight_Implementation(float AxisValue)
{
	if (AxisValue != 0)
    {
		UE_LOG(LogTemp, Warning, TEXT("APingPongPlatform::Server_MoveRight_Implementation"));
    }
    FVector currLocation { GetActorLocation() };
    FVector nextLocation { GetActorLocation() + GetActorRightVector() * MoveSpeed * AxisValue };
    if (!SetActorLocation(nextLocation, true))
    {
    	SetActorLocation(currLocation);
    }
}

// --------------------------------------------------------------------------------------
bool APingPongPlatform::Server_MoveRight_Validate(float AxisValue)
{
	return true;
}

