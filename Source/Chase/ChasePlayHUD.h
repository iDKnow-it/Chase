// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ChasePlayHUD.generated.h"

/**
 * 
 */
UCLASS()
class CHASE_API AChasePlayHUD : public AHUD
{
	GENERATED_BODY()

public:
	//蓝图类的引用，必须在编辑器里指定蓝图类
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD") TSubclassOf<class UChasePlayHUDUserWidget> ChasePlayHUDUserWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD") TSubclassOf<class UDeadPanelUserWidget> DeadPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD") TSubclassOf<class UClearGameUserWidget> ClearGamePanel;

	UPROPERTY() UChasePlayHUDUserWidget* ChasePlayHUDUserWidgetInstance;//保存创建的用户控件实例，防止被GC回收
	UPROPERTY() UDeadPanelUserWidget* DeadPanelInstance;
	UPROPERTY() UClearGameUserWidget* ClearGamePanelInstance;

	void CreateChasePlayHUDUserWidget();
	void CreateDeadPanelUserWidget();
	void CreateClearGameUserWidget();

protected:
	virtual void BeginPlay() override;
};
