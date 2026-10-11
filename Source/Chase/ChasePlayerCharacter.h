// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "HealthInterface.h"
#include "ChasePlayerCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class AChasePlayerController;
class AChasePlayHUD;


UCLASS()
class CHASE_API AChasePlayerCharacter : public ACharacter, public IHealthInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AChasePlayerCharacter();

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh) USkeletalMeshComponent* Mesh1P;

	UPROPERTY(EditAnywhere, Category = "Input") UInputMappingContext* IC_Character;
	UPROPERTY(EditAnywhere, Category = "Input") UInputAction* IA_Move;
	UPROPERTY(EditAnywhere, Category = "Input") UInputAction* IA_Look;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera") class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Health") bool bIsDead = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	virtual void TakeDamage(float Damage) override;
private:
	UPROPERTY(EditAnywhere, Category = "Health") float MaxHealth = 3.f;
	UPROPERTY(VisibleAnywhere, Category = "Health") float CurrentHealth;

	FVector  StartLocation;
	FRotator StartRotation;

	bool bInvincible = false;                                          
	FTimerHandle InvincibleTimer;
	UPROPERTY(EditAnywhere, Category = "Health") float InvincibleTime = 1.0f;
	void EndInvincible();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};
