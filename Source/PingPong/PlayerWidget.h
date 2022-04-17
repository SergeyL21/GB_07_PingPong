// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

class UTextBlock;
class UWidgetSwitcher;

/**
 * 
 */

UCLASS()
class PINGPONG_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* Text_PlayerScore;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_EnemyScore;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher;
	
public:
    virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SwitchWidget(int32 id);
	
	UFUNCTION(BlueprintCallable)
	void UpdatePlayerScore(int newValue);

	UFUNCTION(BlueprintCallable)
	void UpdateEnemyScore(int newValue);
};
