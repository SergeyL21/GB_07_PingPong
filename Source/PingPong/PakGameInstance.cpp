// Fill out your copyright notice in the Description page of Project Settings.

#include "PakGameInstance.h"

#include "DLCLoader.h"

// --------------------------------------------------------------------------------------
TArray<FGameObjectInfo> UPakGameInstance::GetGameObjectsInfo() const
{
	return DLCLoader->GetGameObjectsInfo();
}

// --------------------------------------------------------------------------------------
void UPakGameInstance::Init()
{
	DLCLoader = NewObject<UDLCLoader>(this, "DLC_Loader");
}
