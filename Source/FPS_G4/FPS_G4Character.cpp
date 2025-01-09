// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPS_G4Character.h"

#include "Enemy.h"
#include "FPS_G4Projectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FPS_G4GameMode.h"
#include "HealthandBulletWidget.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AFPS_G4Character

AFPS_G4Character::AFPS_G4Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	Blood = 100.0f;
	BulletNumber = 40;
	
}

void AFPS_G4Character::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPS_G4Character::StartReduceHP()
{
	//开启定时器扣血
	GetWorld()->GetTimerManager().SetTimer(FireReduceHandle,[this]()
	{
		Blood -= 5.0f;
	},1.0,true);
	AFPS_G4GameMode* GameMode = Cast<AFPS_G4GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->HealthandBulletWidget->HealthBar->SetPercent(Blood/100.0f);
}

void AFPS_G4Character::StopReduceHP()
{
	//关闭定时器
	GetWorld()->GetTimerManager().ClearTimer(FireReduceHandle);
	AFPS_G4GameMode* GameMode = Cast<AFPS_G4GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->HealthandBulletWidget->HealthBar->SetPercent(Blood/100.0f);
}

void AFPS_G4Character::UpdateBlood()
{
	AFPS_G4GameMode* GameMode = Cast<AFPS_G4GameMode>(UGameplayStatics::GetGameMode(this));
	GameMode->HealthandBulletWidget->HealthBar->SetPercent(Blood/100.0f);
}

//////////////////////////////////////////////////////////////////////////// Input

void AFPS_G4Character::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AFPS_G4Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFPS_G4Character::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFPS_G4Character::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void AFPS_G4Character::UpdateBulletNumber(int32 BulletNum)
{
	// 将子弹数量转换为FText，这里只是一个例子，你可以根据需要进行格式化
	FText BulletText = FText::FromString(FString::Printf(TEXT("%d"), BulletNumber));

	// 获取UMG
	AFPS_G4GameMode* MyGameMode = Cast<AFPS_G4GameMode>(UGameplayStatics::GetGameMode(this));
	MyGameMode->HealthandBulletWidget->BulletNum->SetText(BulletText);
}

void AFPS_G4Character::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FVector CameraLocation;
	FRotator CameraRotation;
	GetController()->GetPlayerViewPoint(CameraLocation, CameraRotation);

	FVector EndLocation = CameraLocation + (CameraRotation.Vector() * 1000.0f);  // 射线终点，可调整检测长度
	FCollisionQueryParams Params(TEXT("RaycastToEnemy"), false, this);
	FHitResult HitResult;
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, EndLocation, ECC_Pawn, Params);
	AFPS_G4GameMode* GameMode = Cast<AFPS_G4GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (bHit && HitResult.GetActor()->IsA<AEnemy>())
	{
		if(GameMode->CrosshairWidget!=nullptr)
		{
			GameMode->CrosshairWidget->Crosshair->SetColorAndOpacity(HitColor);
		}
	}
	else
	{
		if(GameMode->CrosshairWidget!=nullptr)
		{
			GameMode->CrosshairWidget->Crosshair->SetColorAndOpacity(DefaultColor);
		}
	}
}

void AFPS_G4Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AFPS_G4Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
