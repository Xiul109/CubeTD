// Fill out your copyright notice in the Description page of Project Settings.

#include "Nexus.h"

#include "Enemies/BaseEnemy.h"
#include "Enemies/DivisibleEnemy.h"


void ANexus::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);
	
	Navigable = true;
	CurrentLife = MaxLife;
}

void ANexus::ApplyDamage(float Damage)
{
	CurrentLife -= Damage;
	
	OnDamageDone.Broadcast(Damage, CurrentLife);
}

void ANexus::BeginOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
	ABaseEnemy* Enemy = Cast<ABaseEnemy>(OtherActor);
	if (Enemy) {
		ApplyDamage(Enemy->Damage);

		ADivisibleEnemy* DivisibleEnemy = Cast<ADivisibleEnemy>(Enemy);
		if (DivisibleEnemy)
			DivisibleEnemy->SubdivisionsLeft = 0;

		Enemy->CancelReward = true;
		Enemy->dead = true;
		Enemy->Destroy();
	}
}

void ANexus::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &ANexus::BeginOverlap);
}

