// Fill out your copyright notice in the Description page of Project Settings.

#include "Spawner.h"


void ASpawner::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);
	Navigable = true;
}
