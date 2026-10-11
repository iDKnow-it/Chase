// Fill out your copyright notice in the Description page of Project Settings.


#include "TN_WalkAround.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <NavigationSystem.h>

UTN_WalkAround::UTN_WalkAround()
{
	NodeName = TEXT("Walk Around");

	HangLocation.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UTN_WalkAround, HangLocation));
}

EBTNodeResult::Type UTN_WalkAround::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) { return EBTNodeResult::Failed; }

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) { return EBTNodeResult::Failed; }

	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!Player) { return EBTNodeResult::Failed; }

	UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	FNavLocation RandomLocation;
	
	if (NavigationSystem->GetRandomReachablePointInRadius(Player->GetActorLocation(), 500.f, RandomLocation))
	{
		Blackboard->SetValueAsVector(HangLocation.SelectedKeyName, RandomLocation);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
