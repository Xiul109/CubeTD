// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"
#include "Enemies/BaseEnemy.h"


#include "CubeTDRoundTableRow.generated.h"


USTRUCT(BlueprintType)
struct CUBETD_API FCubeTDRoundTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FCubeTDRoundTableRow()
		: NumberOfEnemies(0)
		, TimeBetweenSpawns(0)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave Info")
	int32 NumberOfEnemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave Info")
	float TimeBetweenSpawns;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave Info")
	TSubclassOf<ABaseEnemy> EnemyClass;
};