// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	UE_LOG(LogTemp, Warning, TEXT("Grabber Constructor"));
	UE_LOG(LogTemp, Warning, TEXT("Grabber Constructor"));
	UE_LOG(LogTemp, Warning, TEXT("Grabber Constructor"));

}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
}

FVector UGrabber::GetMaxGrabLocation() const
{
	return GetComponentLocation() + GetComponentRotation().Vector() * maxGrabDistance;
}

FVector UGrabber::GetHoldLocation() const
{
	return GetComponentLocation() +
			(
				GetComponentRotation().Vector() *
				holdDistance
			);
}

UPhysicsHandleComponent* UGrabber::GetPhysicsComponent() const
{
	return GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}

bool UGrabber::TraceForPhysicsBodies_Implementation(AActor*& actor, UPrimitiveComponent*& primitiveComponent)
{
	return false;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ..
}