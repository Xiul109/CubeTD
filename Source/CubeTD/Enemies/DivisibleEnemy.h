// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemies/BaseEnemy.h"
#include "DivisibleEnemy.generated.h"

/**
 * 
 */
UCLASS()
class CUBETD_API ADivisibleEnemy : public ABaseEnemy
{
	GENERATED_BODY()
	
public:
	ADivisibleEnemy();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Divisible Enemy")
	int SubdivisionsLeft;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Divisible Enemy")
	float StatChangingRatio;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnKilled(AActor* Actor);

	ADivisibleEnemy* CreateDividedEnemy();
};
