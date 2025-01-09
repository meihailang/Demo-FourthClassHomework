// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPS_G4GameMode.h"

#include "FindInBlueprints.h"
#include "FPS_G4Character.h"
#include "HealthandBulletWidget.h"
#include "LoginUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AFPS_G4GameMode::AFPS_G4GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}

void AFPS_G4GameMode::BeginPlay()
{
	Super::BeginPlay();
	// 加载界面类
	TSubclassOf<UULoadingScreenUserWidget>LoadingClass = LoadClass<UULoadingScreenUserWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UMG/LoadingScreenWidget.LoadingScreenWidget_C'"));
	// 创建加载界面的Widget实例
	LoadingScreenWidget = CreateWidget<UULoadingScreenUserWidget>(GetWorld(),LoadingClass);
	if(LoadingScreenWidget != nullptr)
	{
		LoadingScreenWidget->AddToViewport();
	}
	//开始模拟加载
	StartLoadingSimulation();
}

void AFPS_G4GameMode::StartLoadingSimulation()
{
	GetWorld()->GetTimerManager().SetTimer(LoadingTimerHandle,this,&AFPS_G4GameMode::UpdateLoadingProgress,0.1f,true);
}

void AFPS_G4GameMode::ShowLoginWidget()
{
	//加载页面的UMG类
	TSubclassOf<ULoginUserWidget> LoginClass = LoadClass<ULoginUserWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UMG/LoginWidget.LoginWidget_C'"));
	// 创建登录界面的Widget实例
	LoginWidget = CreateWidget<ULoginUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0),LoginClass);
        
	if (LoginWidget)
	{
		LoginWidget->Setup();
		LoginWidget->AddToViewport();
	}
}

void AFPS_G4GameMode::UpdateLoadingProgress()
{
	if (LoadingScreenWidget != nullptr)
	{
		if (LoadingScreenWidget->ProgressBar != nullptr)
		{
			float CurrentProgress = LoadingScreenWidget->ProgressBar->GetPercent();
			if (CurrentProgress < 1.0f)
			{
				LoadingScreenWidget->ProgressBar->SetPercent(FMath::Min(CurrentProgress + 0.01f, 1.0f));
			}
			else
			{
				// 加载完成，关闭加载屏幕
				LoadingScreenWidget->RemoveFromParent();
				GetWorld()->GetTimerManager().ClearTimer(LoadingTimerHandle);
				ShowLoginWidget();	
			}
		}
	}
}

