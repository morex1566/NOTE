// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include <string>

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize and Attach Component
	{
		SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
		if (SpringArmComponent)
		{
			SpringArmComponent->SetupAttachment(RootComponent);
		}

		ThirdPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Third Person Camera"));
		if (ThirdPersonCameraComponent)
		{
			ThirdPersonCameraComponent->SetupAttachment(SpringArmComponent);
		}

		FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
		if (FirstPersonCameraComponent)
		{
			FirstPersonCameraComponent->SetupAttachment(SpringArmComponent);
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

	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainCharacter::OnLook);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::OnMove);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMainCharacter::OnJump);
	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &AMainCharacter::OnRun);
	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AMainCharacter::OnCrouch);
}

void AMainCharacter::OnLook(const FInputActionValue& Value)
{
	const FVector2D& AxisInputValue = Value.Get<FVector2D>();

	GEngine->AddOnScreenDebugMessage(7, 1, FColor::Red, FString::Printf(TEXT("on look X: %f"), AxisInputValue.X));
	GEngine->AddOnScreenDebugMessage(8, 1, FColor::Red, FString::Printf(TEXT("on look Y: %f"), AxisInputValue.Y));


	AddControllerYawInput(AxisInputValue.X);
	AddControllerPitchInput(-AxisInputValue.Y);
}

void AMainCharacter::OnMove(const FInputActionValue& Value)
{
	FQuat			 Rotator		= FQuat(FVector::UpVector, FMath::DegreesToRadians(90));
	const FVector2D& MoveInputValue		= Value.Get<FVector2D>();

	FVector ForwardVector	= GetActorForwardVector();
	FVector RightwardVector = Rotator.RotateVector(ForwardVector);
	FVector MoveVector = (ForwardVector * MoveInputValue.X + RightwardVector * MoveInputValue.Y);
	MoveVector.Normalize(1);

	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, Value.ToString());
	GEngine->AddOnScreenDebugMessage(2, 1, FColor::Red, FString::Printf(TEXT("X: %f"), MoveInputValue.X));
	GEngine->AddOnScreenDebugMessage(3, 1, FColor::Red, FString::Printf(TEXT("Y: %f"), MoveInputValue.Y));
	GEngine->AddOnScreenDebugMessage(4, 1, FColor::Red, MoveVector.ToString());
	GEngine->AddOnScreenDebugMessage(5, 1, FColor::Red, FString::Printf(TEXT("Value: %f"), Value.GetMagnitude()));

	AddMovementInput(MoveVector, Value.GetMagnitude());

}

void AMainCharacter::OnJump(const FInputActionValue& Value)
{
}

void AMainCharacter::OnRun(const FInputActionValue& Value)
{
}

void AMainCharacter::OnCrouch(const FInputActionValue& Value)
{
}
