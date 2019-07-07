// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SplineFollower.h"
#include "BaseEnemy.generated.h"

/**
 * 
 */
UCLASS()
class CUBETD_API ABaseEnemy : public ASplineFollower
{
	GENERATED_BODY()

public:
	ABaseEnemy();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Enemy")
	float MaxLife;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Enemy")
	float Life;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Enemy")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy")
	int Reward;

	bool CancelReward;

	virtual void OnConstruction(const FTransform & Transform) override;
};
