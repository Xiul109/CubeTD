// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Achievement.h"
#include "CubeTDStats.h"

#include "GameFramework/SaveGame.h"
#include "CubeTDSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class CUBETD_API UCubeTDSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 UserIndex;

	UPROPERTY(VisibleAnywhere, Category = Achievements)
	TMap<FString, FAchievement> Achievements;

	UPROPERTY(VisibleAnywhere, Category = Stats)
	TArray<FCubeTDStats> Stats;

	UPROPERTY(VisibleAnywhere, Category = Stats)
	TArray<FString> Names;

	UCubeTDSaveGame();
};
