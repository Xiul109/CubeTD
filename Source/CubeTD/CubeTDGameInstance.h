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
	UAchievementsManager* AchievementeManager;
	
	
};
