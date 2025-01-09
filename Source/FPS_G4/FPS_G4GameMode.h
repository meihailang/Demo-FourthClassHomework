// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CrosshairWidget.h"
#include "HealthandBulletWidget.h"
#include "LoginUserWidget.h"
#include "ULoadingScreenUserWidget.h"
#include "GameFramework/GameModeBase.h"
#include "FPS_G4GameMode.generated.h"

UCLASS(minimalapi)
class AFPS_G4GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFPS_G4GameMode();
	virtual void BeginPlay() override;

	UPROPERTY()
	UULoadingScreenUserWidget* LoadingScreenWidget;
	
	UPROPERTY()
	ULoginUserWidget* LoginWidget;

	UPROPERTY()
	UHealthandBulletWidget* HealthandBulletWidget;
	
	UPROPERTY()
	UCrosshairWidget* CrosshairWidget;
	
	void StartLoadingSimulation();

	void ShowLoginWidget();
	
	//设置一个定时器来模拟加载过程
	FTimerHandle LoadingTimerHandle;
	

	void UpdateLoadingProgress();
	
};



