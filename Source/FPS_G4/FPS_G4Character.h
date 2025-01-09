// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CrosshairWidget.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "FPS_G4Character.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AFPS_G4Character : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;
	
public:
	AFPS_G4Character();

	virtual void BeginPlay() override;
	
	// 玩家最大血量
	UPROPERTY(EditAnywhere,Category="Player Stats")
	float Blood = 100.0f;

	UFUNCTION()
	//更新血量

	//开始扣血
	void StartReduceHP();
	//结束扣血
	void StopReduceHP();

	//更新血量
	void UpdateBlood();

	//时间句柄
	FTimerHandle FireReduceHandle;

	//子弹数目
	int32 BulletNumber;

	//更新子弹数量
	void UpdateBulletNumber(int32 BulletNum);

	void Tick(float DeltaSeconds) override;

	FLinearColor HitColor = FLinearColor(0.0f, 0.0f, 0.0f, 1.0f); // 白色
	FLinearColor DefaultColor = FLinearColor(1.0f, 0.0f, 0.0f, 1.0f); // 红色
	
	void ChangeCrosshair();
	void RestoreCrosshair();
	
protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

