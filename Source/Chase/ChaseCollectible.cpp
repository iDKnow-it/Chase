// Fill out your copyright notice in the Description page of Project Settings.


#include "ChaseCollectible.h"
#include "Components/SphereComponent.h"
#include "ChasePlayerCharacter.h"
#include "ChaseGameState.h"

// Sets default values
AChaseCollectible::AChaseCollectible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ScoreValue = 1;

	CollectibleCollision = CreateDefaultSubobject<USphereComponent>(TEXT("CollectibleCollision"));
	CollectibleCollision->SetSphereRadius(80.f); 
	CollectibleCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	CollectibleCollision->SetGenerateOverlapEvents(true);
	RootComponent = CollectibleCollision;

	CollectibleCollision->OnComponentBeginOverlap.AddDynamic(this, &AChaseCollectible::OnBeginOverlap);//订阅引擎的委托

	CollectibleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollectibleMesh"));
	CollectibleMesh->SetupAttachment(CollectibleCollision);
	CollectibleMesh->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void AChaseCollectible::BeginPlay()
{
	Super::BeginPlay();
	if (AChaseGameState* GameState = GetWorld()->GetGameState<AChaseGameState>())
	{
		GameState->RegisterRemainingCollectibles();
		UE_LOG(LogTemp, Warning, TEXT("？！登记剩余数量！？"));
	}
}

// Called every frame
void AChaseCollectible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChaseCollectible::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (AChasePlayerCharacter* PlayerCharacter = Cast<AChasePlayerCharacter>(OtherActor))
		{
			//直接调用GameState的AddScore函数，增加分数
			if (AChaseGameState* GameState = GetWorld()->GetGameState<AChaseGameState>())
			{
				GameState->AddScore(ScoreValue);
				UE_LOG(LogTemp, Warning, TEXT("？！调用GameState！？"));
			}
			//碰撞到玩家角色时，销毁收集物
			Destroy();
		}
	}
}

