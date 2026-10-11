// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include <Perception/AIPerceptionTypes.h>
#include <BehaviorTree/BehaviorTreeTypes.h>
#include "ChaseEnemyAIController.generated.h"

class UBehaviorTree;
class UAISenseConfig_Sight;
/**
 * 
 */
UCLASS()
class CHASE_API AChaseEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AChaseEnemyAIController();

	UPROPERTY(EditDefaultsOnly, Category = "BehaviorTree") class UBehaviorTree* EnemyBehaviorTree;

	virtual FGenericTeamId GetGenericTeamId() const override { return FGenericTeamId(2); }

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, Category = "AI") TObjectPtr<UAIPerceptionComponent> PerceptionComp;
    UPROPERTY() TObjectPtr<UAISenseConfig_Sight> SightConfig;

	UPROPERTY(EditAnywhere, Category = "Blackboard") FBlackboardKeySelector isFound;

    UFUNCTION()
    void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
