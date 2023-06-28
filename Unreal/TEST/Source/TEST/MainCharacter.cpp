// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"


// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize and Attach Component
	{
		ThirdPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Third Person Camera"));
		if (ThirdPersonCameraComponent)
		{
			ThirdPersonCameraComponent->SetupAttachment(RootComponent);
		}

		FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
		if (FirstPersonCameraComponent)
		{
			FirstPersonCameraComponent->SetupAttachment(RootComponent);
		}
	}
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &AMainCharacter::OnMoveForward);
}

void AMainCharacter::OnMoveForward(const FInputActionValue& Value)
{
	// TODO : 이동하는 함수?
	// 물리 이동 + 좌표 이동

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, Value.ToString());
}

void AMainCharacter::OnMoveBackward(const FInputActionValue& Value)
{

}

void AMainCharacter::OnMoveRightward(const FInputActionValue& Value)
{
}

void AMainCharacter::OnMoveLeftward(const FInputActionValue& Value)
{
}

void AMainCharacter::OnJump(const FInputActionValue& Value)
{
}
