// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "StatsAndAchievements/AchievementsManager.h"

#include "Engine/GameInstance.h"
#include "CubeTDGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CUBETD_API UCubeTDGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UCubeTDGameInstance();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAchievementsManager* AchievementsManager;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FCubeTDStats> Stats;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FString> Names;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CurrentVolume;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CurrentMusicVolume;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BaseTCost;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ShootingTCost;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AoETCost;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SlowTCost;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ExplTCost;
	
	void CleanStats();
	virtual void Shutdown() override;

	UFUNCTION(BlueprintCallable)
	void EraseGameData();

	UFUNCTION(BlueprintCallable)
	void SetVolume(float Volume);
	UFUNCTION(BlueprintCallable)
	void SetMusicVolume(float Volume);
};
