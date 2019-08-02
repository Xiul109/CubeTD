// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "StatsAndAchievements/StatsManager.h"

#include "CubeTDGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class CUBETD_API ACubeTDGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ACubeTDGameStateBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy")
	int Resources;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStatsManager* StatsManager;

private:
	void BeginPlay() override;
};
