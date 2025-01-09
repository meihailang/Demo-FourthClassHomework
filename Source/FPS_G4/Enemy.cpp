// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "FPS_G4Character.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Interfaces/IPluginManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//创建碰撞组件
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBox->SetCollisionObjectType(ECC_WorldStatic);
	CollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	// 绑定开始碰撞事件
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::BeginOverlap);

	// 绑定结束碰撞事件
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AEnemy::EndOverlap);
} 

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor)
	{
		AFPS_G4Character* Character = Cast<AFPS_G4Character>(OtherActor);
		if(Character)
		{
			Character->StartReduceHP();
		}
	}
}

void AEnemy::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if(OtherActor)
	{
		AFPS_G4Character* Character = Cast<AFPS_G4Character>(OtherActor);
		if(Character)
		{
			Character->StopReduceHP();
		}
	}
}




