// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ClearGameUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHASE_API UClearGameUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(meta = (BindWidget)) class UButton* RestartButton;
	UPROPERTY(meta = (BindWidget)) class UButton* ExitButton;

	UFUNCTION() void OnRestartClick();
    UFUNCTION() void OnExitClick();
};
