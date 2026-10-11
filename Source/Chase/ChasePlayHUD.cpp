// Fill out your copyright notice in the Description page of Project Settings.


#include "ChasePlayHUD.h"
#include "ChasePlayHUDUserWidget.h"
#include "DeadPanelUserWidget.h"
#include "ClearGameUserWidget.h"
#include "ChasePlayerCharacter.h"
#include "ChasePlayerController.h"

void AChasePlayHUD::BeginPlay()
{
	Super::BeginPlay();

	CreateChasePlayHUDUserWidget();
}

void AChasePlayHUD::CreateChasePlayHUDUserWidget()
{
	ChasePlayHUDUserWidgetInstance = CreateWidget<UChasePlayHUDUserWidget>(GetOwningPlayerController(), ChasePlayHUDUserWidgetClass);
	if (ChasePlayHUDUserWidgetInstance)
	{
		ChasePlayHUDUserWidgetInstance->AddToViewport();
	}	
}

void AChasePlayHUD::CreateDeadPanelUserWidget()
{
	if (AChasePlayerController* PlayerController = Cast<AChasePlayerController>(GetOwningPlayerController()))
	{
		if (AChasePlayHUD* HUD = Cast<AChasePlayHUD>(PlayerController->GetHUD()))
		{
			if (DeadPanelInstance == nullptr)
			{
				DeadPanelInstance = CreateWidget<UDeadPanelUserWidget>(PlayerController, DeadPanel);
				if (DeadPanelInstance)
				{
					DeadPanelInstance->AddToViewport();
				}
			}
		}
	}
}

void AChasePlayHUD::CreateClearGameUserWidget()
{
	if (AChasePlayerController* PlayerController = Cast<AChasePlayerController>(GetOwningPlayerController()))
	{
		if (AChasePlayHUD* HUD = Cast<AChasePlayHUD>(PlayerController->GetHUD()))
		{
			if (ClearGamePanelInstance == nullptr)
			{
				ClearGamePanelInstance = CreateWidget<UClearGameUserWidget>(PlayerController, ClearGamePanel);
				if (ClearGamePanelInstance)
				{
					ClearGamePanelInstance->AddToViewport();
				}
			}
		}
	}
}
