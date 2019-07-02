// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseEnemy.h"


ABaseEnemy::ABaseEnemy() : MaxLife(100), Damage(1) {}

void ABaseEnemy::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);

	Life = MaxLife;
}
