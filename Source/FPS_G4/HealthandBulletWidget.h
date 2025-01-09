// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "HealthandBulletWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPS_G4_API UHealthandBulletWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* BulletNum;
};
