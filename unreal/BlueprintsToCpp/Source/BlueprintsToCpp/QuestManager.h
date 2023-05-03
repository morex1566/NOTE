// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestInfo.h"
#include "GameFramework/Actor.h"
#include "QuestManager.generated.h"

UCLASS()
class BLUEPRINTSTOCPP_API AQuestManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuestManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	int GetQuestIndex(FName questId);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetFour();

	UFUNCTION(BlueprintCosmetic)

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void CompleteQuest(FName questId, bool completeWholeQuest);

	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FQuestInfo> questList;
};
