// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "CrosshairWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPS_G4_API UCrosshairWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UImage* Crosshair;  // 用于显示十字准星图片的UImage控件指针
	
};
