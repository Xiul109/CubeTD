// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseEnemy.h"


ABaseEnemy::ABaseEnemy() : MaxLife(1), Damage(1), Reward(1), CancelReward(false) {}

void ABaseEnemy::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);

	Life = MaxLife;
}

void ABaseEnemy::TakeDamage(float Damage)
{
	if (Damage > 0.f)
	{
		Life -= Damage;
		//If the damage kills enemy, destroy the actor
		if (Life <= 0.f)
		{
			Destroy();
		}
	}
}
