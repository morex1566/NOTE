// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "InputAction.h"

#include "MainCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;


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

	void OnLook(const FInputActionValue& Value);
	void OnMove(const FInputActionValue& Value);
	void OnJump(const FInputActionValue& Value);
	void OnRun(const FInputActionValue& Value);
	void OnCrouch(const FInputActionValue& Value);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCameraComponent> ThirdPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCameraComponent> FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditAnywhere, Category = Input, DisplayName = "Input")
		TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category = Input, DisplayName = "Look Action")
		TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = Input, DisplayName = "Move Action")
		TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = Input, DisplayName = "Jump Action")
		TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = Input, DisplayName = "Run Action")
		TObjectPtr<UInputAction> RunAction;

	UPROPERTY(EditAnywhere, Category = Input, DisplayName = "Crouch Action")
		TObjectPtr<UInputAction> CrouchAction;
};
