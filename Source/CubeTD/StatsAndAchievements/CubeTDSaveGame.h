// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Achievement.h"

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
	TMap<FString, FAchievement> Achievements;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 UserIndex;
	
	UCubeTDSaveGame();
};
