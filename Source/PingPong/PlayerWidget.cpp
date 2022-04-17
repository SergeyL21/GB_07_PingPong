// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerWidget.h"

#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"

// --------------------------------------------------------------------------------------
void UPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

// --------------------------------------------------------------------------------------
void UPlayerWidget::SwitchWidget(int32 windowId)
{
	WidgetSwitcher->SetActiveWidgetIndex(windowId);
}

// --------------------------------------------------------------------------------------
void UPlayerWidget::UpdatePlayerScore(int newValue)
{
	if (Text_PlayerScore)
	{
		TArray<FStringFormatArg> Args;
		Args.Add(FStringFormatArg(newValue));
		auto String { FString::Format(TEXT("Player score: {0}") , Args) };
		Text_PlayerScore->SetText(FText::FromString(String));
	}
}

// --------------------------------------------------------------------------------------
void UPlayerWidget::UpdateEnemyScore(int newValue)
{
	if (Text_EnemyScore)
	{
		TArray<FStringFormatArg> Args;
		Args.Add(FStringFormatArg(newValue));
		auto String { FString::Format(TEXT("Enemy score: {0}") , Args) };
		Text_EnemyScore->SetText(FText::FromString(String));
	}
}




