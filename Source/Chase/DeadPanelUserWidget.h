// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DeadPanelUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHASE_API UDeadPanelUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(meta = (BindWidget)) class UButton* RestartButton;
	UPROPERTY(meta = (BindWidget)) class UButton* ExitButton;
	UPROPERTY(meta = (BindWidget)) class UTextBlock* FinalScore;

	UFUNCTION()
	void OnFinalScoreTextChanged(int32 NewScore, int32 RemainingCollectibles);

    UFUNCTION()
	void OnRestartClick();
	UFUNCTION()
	void OnExitClick();
};
