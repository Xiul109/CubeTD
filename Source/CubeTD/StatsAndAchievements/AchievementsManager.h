// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CubeTDStats.h"
#include "Achievement.h"

#include "UObject/NoExportTypes.h"
#include "AchievementsManager.generated.h"


/**
 * 
 */
UCLASS()
class CUBETD_API UAchievementsManager : public UObject
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAchievementDelegate, FAchievement, Achievement);
	
public:
	UAchievementsManager();

	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FAchievement> Achievements;
	
	UFUNCTION()
	void UpdateAchievements(const FCubeTDStats &Stats, const uint8 Type = 0);

	//Delegates
	UPROPERTY(BlueprintAssignable)
	FAchievementDelegate OnAchievementObtained;

	virtual void BeginDestroy() override;

protected:
	void UpdateAchievementProgression(const FString Name, const float Threshold, const float Value);
};
