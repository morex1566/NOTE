// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "InputAction.h"

#include "MainCharacter.generated.h"

class UCameraComponent;


UCLASS()
class TEST_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnMoveForward(const FInputActionValue& Value);
	void OnMoveBackward(const FInputActionValue& Value);
	void OnMoveRightward(const FInputActionValue& Value);
	void OnMoveLeftward(const FInputActionValue& Value);
	void OnJump(const FInputActionValue& Value);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCameraComponent> ThirdPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCameraComponent> FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, Category = Input, DisplayName = "입력 매핑 컨텍스트")
		TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category = Input, DisplayName = "수직 이동 액션")
		TObjectPtr<UInputAction> InputAction;


	UPROPERTY(EditAnywhere, Category = "캐릭터 스테이터스", DisplayName = "속도")
	float Speed;
};
