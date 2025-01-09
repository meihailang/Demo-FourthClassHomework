// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "ULoadingScreenUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPS_G4_API UULoadingScreenUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* ProgressBar;

};
