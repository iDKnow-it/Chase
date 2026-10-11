// Fill out your copyright notice in the Description page of Project Settings.


#include "ChaseGameState.h"

void AChaseGameState::AddScore(int32 ScoreToAdd)
{
	if (!HasAuthority()) { return; }//确保只有服务器端可以修改分数，防止客户端作弊
	PlayerScore += ScoreToAdd;
	RemainingCollectibles = FMath::Max(0, RemainingCollectibles - 1);
	OnScoreChanged.Broadcast(PlayerScore, RemainingCollectibles);//广播分数变化事件，通知所有订阅者
	UE_LOG(LogTemp, Warning, TEXT("格兰芬多加一分！（邓布利多脸）"));
}

void AChaseGameState::RegisterRemainingCollectibles()
{
	if (!HasAuthority()) { return; }//确保只有服务器端可以修改分数，防止客户端作弊
	++AChaseGameState::RemainingCollectibles;
	OnScoreChanged.Broadcast(PlayerScore, RemainingCollectibles);//广播分数变化事件，通知所有订阅者
}


