// Fill out your copyright notice in the Description page of Project Settings.

#include "WiggleEnemy.h"

AWiggleEnemy::AWiggleEnemy(): MinAmplitude(2), MaxAmplitude(10), MinFrequency(0.2), MaxFrequency(5), AccumulatedTime(0){}

void AWiggleEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AccumulatedTime += DeltaTime;

	float OffsetX = AmplitudeX * FMath::Sin(FrequencyX*AccumulatedTime*2*PI+PhaseX);
	float OffsetY = AmplitudeY * FMath::Sin(FrequencyY*AccumulatedTime * 2 * PI + PhaseY);
	float OffsetZ = AmplitudeZ * FMath::Sin(FrequencyZ*AccumulatedTime * 2 * PI + PhaseZ);

	AddActorWorldOffset(FVector(OffsetX,OffsetY,OffsetZ));
}

void AWiggleEnemy::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);

	PhaseX     = FMath::RandRange(0.0f, 2*PI);
	AmplitudeX = FMath::RandRange(MinAmplitude, MaxAmplitude);
	FrequencyX = FMath::RandRange(MinFrequency, MaxFrequency);

	PhaseY = FMath::RandRange(0.0f, 2 * PI);
	AmplitudeY = FMath::RandRange(MinAmplitude, MaxAmplitude);
	FrequencyY = FMath::RandRange(MinFrequency, MaxFrequency);

	PhaseZ = FMath::RandRange(0.0f, 2 * PI);
	AmplitudeZ = FMath::RandRange(MinAmplitude, MaxAmplitude);
	FrequencyZ = FMath::RandRange(MinFrequency, MaxFrequency);
}
