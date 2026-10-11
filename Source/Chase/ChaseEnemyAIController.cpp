// Fill out your copyright notice in the Description page of Project Settings.


#include "ChaseEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

AChaseEnemyAIController::AChaseEnemyAIController()
{
    PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

    SightConfig->SightRadius = 2000.f;
    SightConfig->LoseSightRadius = 2400.f;
    SightConfig->PeripheralVisionAngleDegrees = 75.f;
    SightConfig->AutoSuccessRangeFromLastSeenLocation = 0.f;

    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

    PerceptionComp->ConfigureSense(*SightConfig);
    PerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());

    PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AChaseEnemyAIController::OnPerceptionUpdated);
}

void AChaseEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	if (EnemyBehaviorTree)
	{
		RunBehaviorTree(EnemyBehaviorTree);
	}
}

void AChaseEnemyAIController::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    if (Blackboard)
    {

        if (UCharacterMovementComponent* Move = GetCharacter()->GetCharacterMovement())
        {
            Move->MaxWalkSpeed = Stimulus.WasSuccessfullySensed() ? 1600.f : 200.f;
        }

        if (Stimulus.WasSuccessfullySensed())
        {
            Blackboard->SetValueAsVector(TEXT("PlayerCurrentLocation"), Actor->GetActorLocation());
            Blackboard->SetValueAsBool(TEXT("isFound"), true);
        }
        else
        {
            Blackboard->ClearValue(TEXT("PlayerCurrentLocation"));
            Blackboard->SetValueAsBool(TEXT("isFound"), false);
        }
    }
}


