// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "ChaseGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnScoreChanged, int32, NewScore, int32, RemainingCollectibles);
/**
 * 
 */
UCLASS()
class CHASE_API AChaseGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "GameScore") int32 PlayerScore = 0;
	UPROPERTY(BlueprintReadOnly, Category = "GameScore") int32 RemainingCollectibles = 0;
	UPROPERTY(BlueprintAssignable) FOnScoreChanged OnScoreChanged;//声明一个委托“类型”，用于在分数变化时通知订阅者

	void AddScore(int32 ScoreToAdd);
	void RegisterRemainingCollectibles();
};
