// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameObjectAsset.h"
#include "Engine/GameInstance.h"
#include "PakGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API UPakGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	class UDLCLoader* DLCLoader;
	
public:
	UFUNCTION(BlueprintCallable)
	TArray<FGameObjectInfo> GetGameObjectsInfo() const;
	
protected:
	virtual void Init() override;

};
