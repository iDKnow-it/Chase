// Fill out your copyright notice in the Description page of Project Settings.


#include "ClearGameUserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UClearGameUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (RestartButton) { RestartButton->OnClicked.AddDynamic(this, &UClearGameUserWidget::OnRestartClick); }
	if (ExitButton) { ExitButton->OnClicked.AddDynamic(this, &UClearGameUserWidget::OnExitClick); }

	if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		PC->bShowMouseCursor = true;
		PC->SetInputMode(FInputModeGameAndUI());
	}
}

void UClearGameUserWidget::OnRestartClick()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()));
}

void UClearGameUserWidget::OnExitClick()
{
	UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(this, 0), EQuitPreference::Quit, false);
}

void UClearGameUserWidget::NativeDestruct()
{
	if (RestartButton) { RestartButton->OnClicked.RemoveDynamic(this, &UClearGameUserWidget::OnRestartClick); }
	if (ExitButton) { ExitButton->OnClicked.RemoveDynamic(this, &UClearGameUserWidget::OnExitClick); }

	if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		PC->bShowMouseCursor = false;
		PC->SetInputMode(FInputModeGameOnly());
	}

	Super::NativeDestruct();
}
