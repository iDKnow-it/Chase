// Fill out your copyright notice in the Description page of Project Settings.


#include "TN_FindPlayerLocation.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"

UTN_FindPlayerLocation::UTN_FindPlayerLocation()
{
	NodeName = TEXT("Find Player Location");

	TargetLocation.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UTN_FindPlayerLocation, TargetLocation));
}

EBTNodeResult::Type UTN_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) { return EBTNodeResult::Failed; }

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) { return EBTNodeResult::Failed; }

	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!Player) { return EBTNodeResult::Failed; }
    
	Blackboard->SetValueAsVector(TargetLocation.SelectedKeyName, Player->GetActorLocation());

	return EBTNodeResult::Succeeded;
}
