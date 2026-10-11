// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include "ChasePlayHUDUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHASE_API UChasePlayHUDUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

    UFUNCTION()
    void HandleScoreChanged(int32 NewScore, int32 RemainingCollectibles); //必须有UFUNCTION()防止被GC回收;参数表要和委托类型一字不差

	UPROPERTY(meta = (BindWidget)) UTextBlock* ScoreText;//meta = (BindWidget)让引擎知道这个变量是和蓝图里同名的控件绑定的,只要存在这样的变量即可，不需要手动绑定                    

    UPROPERTY(meta = (BindWidget)) UTextBlock* RemainingText;                 

};
