// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TN_FindPlayerLocation.generated.h"

/**
 * 
 */
UCLASS()
class CHASE_API UTN_FindPlayerLocation : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UTN_FindPlayerLocation();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard") FBlackboardKeySelector TargetLocation;
};
