// Fill out your copyright notice in the Description page of Project Settings.


#include "DeadPanelUserWidget.h"
#include "Components/Button.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include <Components/TextBlock.h>
#include "ChaseGameState.h"

void UDeadPanelUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (AChaseGameState* GameState = GetWorld()->GetGameState<AChaseGameState>())
	{
		//绑定:把我的处理函数写进GameState的名单
		GameState->OnScoreChanged.AddDynamic(this, &UDeadPanelUserWidget::OnFinalScoreTextChanged);

		//绑完补读一次,获得初始分数和剩余数量
		OnFinalScoreTextChanged(GameState->PlayerScore, GameState->RemainingCollectibles);
	}

	//唤出鼠标:显示光标 + 切到"游戏和UI"输入模式,按钮才能点
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		PC->bShowMouseCursor = true;
		PC->SetInputMode(FInputModeGameAndUI());
	}

	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UDeadPanelUserWidget::OnRestartClick);
	}
	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UDeadPanelUserWidget::OnExitClick);
	}
}

void UDeadPanelUserWidget::NativeDestruct()
{

	if (AChaseGameState* GameState = GetWorld()->GetGameState<AChaseGameState>())
	{
		GameState->OnScoreChanged.RemoveDynamic(this, &UDeadPanelUserWidget::OnFinalScoreTextChanged);
	}

	//面板关闭时恢复:隐藏鼠标 + 回到纯游戏输入模式
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		PC->bShowMouseCursor = false;
		PC->SetInputMode(FInputModeGameOnly());
	}

	if (RestartButton)
	{
		RestartButton->OnClicked.RemoveDynamic(this, &UDeadPanelUserWidget::OnRestartClick);
	}
	if (ExitButton)
	{
		ExitButton->OnClicked.RemoveDynamic(this, &UDeadPanelUserWidget::OnExitClick);
	}

	Super::NativeDestruct();
}

void UDeadPanelUserWidget::OnFinalScoreTextChanged(int32 NewScore, int32 RemainingCollectibles)
{
	FinalScore->SetText(FText::FromString(FString::Printf(TEXT("%d"), NewScore)));
}

void UDeadPanelUserWidget::OnRestartClick()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()));
}

void UDeadPanelUserWidget::OnExitClick()
{
	UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(this, 0), EQuitPreference::Quit, false);
}
