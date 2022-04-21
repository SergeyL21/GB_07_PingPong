// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PingPongPlatform.generated.h"

struct FStreamableHandle;

UCLASS()
class PINGPONG_API APingPongPlatform : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UBoxComponent* BodyCollision;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* BodyMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSoftObjectPtr<UStaticMesh> BodyMeshRef;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed { 100.f };

	TSharedPtr<FStreamableHandle> AssetHandle;
	
public:
	APingPongPlatform();
	
protected:
	virtual void BeginPlay() override;
	
public:
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_MoveRight(float AxisValue);
	
	void LoadBodyMesh();

	void OnBodyMeshLoaded();
};
