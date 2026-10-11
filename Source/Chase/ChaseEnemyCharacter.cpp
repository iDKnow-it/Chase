// Fill out your copyright notice in the Description page of Project Settings.


#include "ChaseEnemyCharacter.h"
#include "ChaseEnemyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SphereComponent.h"
#include "ChasePlayerCharacter.h"
#include "HealthInterface.h"

// Sets default values
AChaseEnemyCharacter::AChaseEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AChaseEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCharacterMovement()->MaxWalkSpeed = 200.f;

	AttackZone = CreateDefaultSubobject<USphereComponent>(TEXT("AttackZone"));
	AttackZone->SetSphereRadius(100.f);
	AttackZone->SetupAttachment(RootComponent);
	AttackZone->SetRelativeLocation(FVector(10.f, 0.f, 30.f));
	AttackZone->OnComponentBeginOverlap.AddDynamic(this, &AChaseEnemyCharacter::OnBeginOverlap);
}

// Called when the game starts or when spawned
void AChaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AChaseEnemyCharacter::ResetAttack()
{
	bAttackReady = true;
}

// Called every frame
void AChaseEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AChaseEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AChaseEnemyCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bAttackReady) { return; }


	if (IHealthInterface* Interface = Cast<IHealthInterface>(OtherActor))
	{
		bAttackReady = false;
		Interface->TakeDamage(Damage);

		GetWorldTimerManager().SetTimer(AttackCooldownTimer, this, &AChaseEnemyCharacter::ResetAttack, AttackInterval, false);
	}
}

