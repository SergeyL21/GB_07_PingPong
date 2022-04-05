// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PingPongPlatform.generated.h"

UCLASS()
class PINGPONG_API APingPongPlatform : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UBoxComponent* BodyCollision;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* BodyMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed { 100.f };
	
public:
	APingPongPlatform();
	
protected:
	virtual void BeginPlay() override;
	
public:
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_MoveRight(float AxisValue);
};
