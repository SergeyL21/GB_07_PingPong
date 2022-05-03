// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/PrimaryAssetLabel.h"
#include "UObject/NoExportTypes.h"
#include "GameObjectAsset.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FGameObjectInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Description;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FSoftObjectPath PrimaryAsset;
	UPROPERTY()
	UPrimaryAssetLabel* PrimaryAssetLabel;

	FORCEINLINE FText GetGameObjectName() const { return Name; }
	
	FORCEINLINE FText GetGameObjectDescription() const { return Description; }
	
	FString GetGameObjectReference();
};

UCLASS()
class PINGPONG_API UMapInfoBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	/*Blueprint Function to return the value from the struct*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GameObjectInfo | Methods")
	static FString GetGameObjectReference(UPARAM(ref) FGameObjectInfo& MyStructRef) {
		return MyStructRef.GetGameObjectReference();
	};
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PINGPONG_API UGameObjectAsset : public UObject
{
	GENERATED_BODY()

public:
    UGameObjectAsset(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer) {}
	
    UPROPERTY(EditAnywhere)
    FGameObjectInfo GameObjectInfo;
};
