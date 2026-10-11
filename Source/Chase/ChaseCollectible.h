// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChaseCollectible.generated.h"

UCLASS()
class CHASE_API AChaseCollectible : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChaseCollectible();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collectible") class UStaticMeshComponent* CollectibleMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collectible") class USphereComponent* CollectibleCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collectible") int32 ScoreValue;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//声明一个函数，用于处理碰撞事件，其本质是引擎提供的一个回调函数，当碰撞发生时会被调用，cpp中有关于该函数的订阅
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
