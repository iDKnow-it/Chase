// Fill out your copyright notice in the Description page of Project Settings.


#include "ChasePlayHUDUserWidget.h"
#include "Components/TextBlock.h"
#include "ChaseGameState.h"

void UChasePlayHUDUserWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (AChaseGameState* GameState = GetWorld()->GetGameState<AChaseGameState>())
    {
        //绑定:把我的处理函数写进 GameState 的名单
        GameState->OnScoreChanged.AddDynamic(this, &UChasePlayHUDUserWidget::HandleScoreChanged);

		//绑完补读一次,获得初始分数和剩余数量
        HandleScoreChanged(GameState->PlayerScore, GameState->RemainingCollectibles);
    }
}

void UChasePlayHUDUserWidget::HandleScoreChanged(int32 NewScore, int32 RemainingCollectibles)
{
    if (ScoreText)
    {
        ScoreText->SetText(FText::FromString(FString::Printf(TEXT("%d"), NewScore)));
    }
    if (RemainingText)
    {
        RemainingText->SetText(FText::FromString(FString::Printf(TEXT("%d"), RemainingCollectibles)));
    }
}

void UChasePlayHUDUserWidget::NativeDestruct()//这其实和析构函数类似，所以调用顺序和预定相反，先退订再调用父类的NativeDestruct
{
    if (AChaseGameState* GameState = GetWorld()->GetGameState<AChaseGameState>())
    {
        GameState->OnScoreChanged.RemoveDynamic(this, &UChasePlayHUDUserWidget::HandleScoreChanged);
    }

    Super::NativeDestruct();
}

