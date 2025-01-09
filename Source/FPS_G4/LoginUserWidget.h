// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginUserWidget.generated.h"
class UEditableText;
class UButton;
/**
 * 
 */
UCLASS()
class FPS_G4_API ULoginUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	
	// 用于获取用户名输入框的指针
	UPROPERTY(meta = (BindWidget))
	UEditableText* UsernameInput;

	// 用于获取密码输入框的指针
	UPROPERTY(meta = (BindWidget))
	UEditableText* PasswordInput;

	// 用于获取确认按钮的指针
	UPROPERTY(meta = (BindWidget))
	UButton* ConfirmButton;

	// 函数用于设置和初始化登录界面相关逻辑
	void Setup();

	// 函数用于处理确认按钮点击事件
	UFUNCTION()
	void OnConfirmButtonClicked();
};
