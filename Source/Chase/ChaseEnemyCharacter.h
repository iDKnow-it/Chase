// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ChaseEnemyCharacter.generated.h"

UCLASS()
class CHASE_API AChaseEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AChaseEnemyCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage") class USphereComponent* AttackZone;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Damage") float Damage = 1.f;
	UPROPERTY(EditAnywhere, Category = "Damage") float AttackInterval = 1.f;
	bool bAttackReady = true;
	FTimerHandle AttackCooldownTimer;
	void ResetAttack();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
