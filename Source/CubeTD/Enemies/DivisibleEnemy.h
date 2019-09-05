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

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDivisionDelegate, ADivisibleEnemy*, Child1, ADivisibleEnemy*, Child2);
	
public:
	ADivisibleEnemy();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Divisible Enemy")
	int SubdivisionsLeft;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Divisible Enemy")
	float StatChangingRatio;

	FOnDivisionDelegate OnDivision;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnKilled(AActor* Actor);

	ADivisibleEnemy* CreateDividedEnemy();
};
