// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginUserWidget.h"

#include "FPS_G4Character.h"
#include "FPS_G4GameMode.h"
#include "LocalizationDescriptor.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Kismet/GameplayStatics.h"


// 设置登录界面相关逻辑，比如绑定按钮点击事件等
void ULoginUserWidget::Setup()
{
	if (ConfirmButton)
	{
		ConfirmButton->OnClicked.AddDynamic(this, &ULoginUserWidget::OnConfirmButtonClicked);
	}
}

// 处理确认按钮点击事件
void ULoginUserWidget::OnConfirmButtonClicked()
{
	FString Username = UsernameInput->GetText().ToString();
	FString Password = PasswordInput->GetText().ToString();

	// 可以添加验证逻辑，比如和后端服务器验证用户名和密码是否正确等
	// 暂时只是简单打印，后续可以替换为真实的验证逻辑
	UE_LOG(LogTemp, Warning, TEXT("用户名: %s，密码: %s"), *Username, *Password);
	AFPS_G4GameMode* GameMode = Cast<AFPS_G4GameMode>(UGameplayStatics::GetGameMode(this));
	GameMode->LoginWidget->RemoveFromParent();
	TSubclassOf<UHealthandBulletWidget> HealthandBullteClass = LoadClass<UHealthandBulletWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UMG/BloodandBullte.BloodandBullte_C'"));
	GameMode->HealthandBulletWidget = CreateWidget<UHealthandBulletWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0),HealthandBullteClass);
	AFPS_G4Character* MyCharactor = Cast<AFPS_G4Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	FText BulletText = FText::FromString(FString::Printf(TEXT("%d"), MyCharactor->BulletNumber));
	GameMode->HealthandBulletWidget->BulletNum->SetText(BulletText);
	if(GameMode->HealthandBulletWidget)
	{
		GameMode->HealthandBulletWidget->AddToViewport();
	}
	UClass* CrosshairWidgetClass = LoadClass<UCrosshairWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UMG/CrosshairWidget.CrosshairWidget_C'"));
	if(CrosshairWidgetClass)
	{
		GameMode->CrosshairWidget = CreateWidget<UCrosshairWidget>(GetWorld(), CrosshairWidgetClass);
		if (GameMode->CrosshairWidget)
		{
			GameMode->CrosshairWidget->AddToViewport();
		}
	}
	FLinearColor DefaultColor = FLinearColor(1.0f, 0.0f, 0.0f, 1.0f); // 红色
	GameMode->CrosshairWidget->SetColorAndOpacity(DefaultColor);
}
