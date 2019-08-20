// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AchievementsManager.h"
#include "CubeTDStats.h"

#include "UObject/NoExportTypes.h"
#include "StatsManager.generated.h"


/**
 * 
 */
UCLASS()
class CUBETD_API UStatsManager : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	UAchievementsManager* AchievementsManagerRef;

	void SetAchievementsManagerRef(UAchievementsManager* ref);


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FCubeTDStats CurrentGameStats;


	UFUNCTION(BlueprintCallable)
	void UpdateEnemiesKilled();
	UFUNCTION(BlueprintCallable)
	void UpdateTowersBuilt();
	UFUNCTION(BlueprintCallable)
	void UpdateResourcesGained(int Resources);
	UFUNCTION(BlueprintCallable)
	void UpdateMazeLenght(int NewLenght);
	UFUNCTION(BlueprintCallable)
	void UpdateRoundsWon();

protected:
	void UpdateAchievementsManager();
};
