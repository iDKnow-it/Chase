// Fill out your copyright notice in the Description page of Project Settings.


#include "ChasePlayerCharacter.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "ChasePlayerController.h"
#include "ChasePlayHUD.h"


// Sets default values
AChasePlayerCharacter::AChasePlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	Camera->SetupAttachment(GetCapsuleComponent());
	Camera->SetRelativeLocation(FVector(30.f, 0.f, 65.f));
	Camera->bUsePawnControlRotation = true;

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(Camera);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(FVector(-25.f, 0.f, -160.f));

	GetCharacterMovement()->MaxWalkSpeed = 1500.f;

	CurrentHealth = MaxHealth;

}

// Called when the game starts or when spawned
void AChasePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
	StartRotation = GetActorRotation();
}

void AChasePlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AChasePlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AChasePlayerCharacter::TakeDamage(float Damage)
{
	if (bIsDead || bInvincible) { return; }

	CurrentHealth -= Damage;

	bInvincible = true;
	GetWorldTimerManager().SetTimer(InvincibleTimer, this, &AChasePlayerCharacter::EndInvincible, InvincibleTime, false);

	if (CurrentHealth <= 0)
	{
		bIsDead = true;
		UE_LOG(LogTemp, Warning, TEXT("YOU DEAD!"));

		if (AChasePlayerController* PlayerController = Cast<AChasePlayerController>(GetController()))
		{
			if (AChasePlayHUD* HUD = Cast<AChasePlayHUD>(PlayerController->GetHUD()))
			{
				PlayerController->bShowMouseCursor = true;
				PlayerController->SetInputMode(FInputModeGameAndUI());

				HUD->CreateDeadPanelUserWidget();
			}
		}
	}

	SetActorLocationAndRotation(StartLocation, StartRotation, false, nullptr, ETeleportType::TeleportPhysics);
	GetCharacterMovement()->StopMovementImmediately();
	if (AController* C = GetController()) { C->SetControlRotation(StartRotation); }
	
}

void AChasePlayerCharacter::EndInvincible()
{
	bInvincible = false;
}

// Called every frame
void AChasePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AChasePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedPlayerInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedPlayerInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AChasePlayerCharacter::Move);
		EnhancedPlayerInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AChasePlayerCharacter::Look);

		if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
		{
			UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

			InputSubsystem->AddMappingContext(IC_Character, 0);
		}
	}
}


