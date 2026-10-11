// Fill out your copyright notice in the Description page of Project Settings.


#include "EndRoom.h"
#include "Components/BoxComponent.h"
#include "ChasePlayerController.h"
#include "ChasePlayerCharacter.h"
#include "ChasePlayHUD.h"
#include "ClearGameUserWidget.h"
#include "ChaseGameState.h"

// Sets default values
AEndRoom::AEndRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ClearGameRoom = CreateDefaultSubobject<UBoxComponent>(TEXT("ClearGameRoom"));
	ClearGameRoom->OnComponentBeginOverlap.AddDynamic(this, &AEndRoom::OnBeginOverlap);
}

// Called when the game starts or when spawned
void AEndRoom::BeginPlay()
{
	Super::BeginPlay();
	
	if (AChaseGameState* GS = Cast<AChaseGameState>(GetWorld()->GetGameState()))
	{
		GS->OnScoreChanged.AddDynamic(this, &AEndRoom::IsScoreFull);
	}
}

void AEndRoom::IsScoreFull(int32 NewScore, int32 RemainingCollectibles)
{
	if (RemainingCollectibles == 0) { bIsScoreFull = true; }
}

// Called every frame
void AEndRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEndRoom::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AChaseGameState* GS = Cast<AChaseGameState>(GetWorld()->GetGameState()))
	{
		IsScoreFull(GS->PlayerScore, GS->RemainingCollectibles);
		GS->OnScoreChanged.RemoveDynamic(this, &AEndRoom::IsScoreFull);
	}
	
	if (!bIsScoreFull) { return; }

	if (AChasePlayerCharacter* Player = Cast<AChasePlayerCharacter>(OtherActor))
	{
		if (AChasePlayerController* PC = Cast<AChasePlayerController>(Player->GetController()))
		{
			if (AChasePlayHUD* HUD = Cast<AChasePlayHUD>(PC->GetHUD()))
			{
				PC->bShowMouseCursor = true;
				PC->SetInputMode(FInputModeGameAndUI());

				HUD->CreateClearGameUserWidget();
			}
		}
	}
}