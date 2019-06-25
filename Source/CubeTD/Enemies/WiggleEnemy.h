// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemies/BaseEnemy.h"
#include "WiggleEnemy.generated.h"

/**
 * 
 */
UCLASS()
class CUBETD_API AWiggleEnemy : public ABaseEnemy
{
	GENERATED_BODY()
	
public:
	AWiggleEnemy();

	//Random Ranges for amplitude and frequency
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wiggle Enemy")
	float MinAmplitude;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wiggle Enemy")
	float MaxAmplitude;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wiggle Enemy")
	float MinFrequency;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wiggle Enemy")
	float MaxFrequency;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wiggle Enemy", meta = (AllowPrivateAccess = "true"))
	float AmplitudeX;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wiggle Enemy", meta = (AllowPrivateAccess = "true"))
	float FrequencyX;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wiggle Enemy", meta = (AllowPrivateAccess = "true"))
	float PhaseX;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wiggle Enemy", meta = (AllowPrivateAccess = "true"))
	float AmplitudeY;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wiggle Enemy", meta = (AllowPrivateAccess = "true"))
	float FrequencyY;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wiggle Enemy", meta = (AllowPrivateAccess = "true"))
	float PhaseY;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wiggle Enemy", meta = (AllowPrivateAccess = "true"))
	float AmplitudeZ;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wiggle Enemy", meta = (AllowPrivateAccess = "true"))
	float FrequencyZ;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wiggle Enemy", meta = (AllowPrivateAccess = "true"))
	float PhaseZ;

	float AccumulatedTime;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void OnConstruction(const FTransform & Transform) override;
};
