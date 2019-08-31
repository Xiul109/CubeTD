// Fill out your copyright notice in the Description page of Project Settings.

#include "ExplosiveTrap.h"



AExplosiveTrap::AExplosiveTrap()
{
	//Cooldown of the damage event
	damage = 0.15;
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AExplosiveTrap::BeginOverlap);
}


void AExplosiveTrap::Tick(float DeltaTime)
{
	if (Activated) {
		AccumulatedDeltaTime += DeltaTime;
			DamageEnemies();
		if (AccumulatedDeltaTime >= Durability) {
			Destroy();
		}
	}
}

void AExplosiveTrap::BeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	ABaseEnemy* ActorCol = Cast<ABaseEnemy>(OtherActor);
	if (ActorCol != nullptr) {
		Activated = true;
	}
}

void AExplosiveTrap::DamageEnemies() {
	TArray<AActor*> Enemies;
	CollisionComp->GetOverlappingActors(Enemies, ABaseEnemy::StaticClass());
	for (AActor* enemy : Enemies) {
		class ABaseEnemy* CurrentEnemy = Cast<ABaseEnemy>(enemy);
		CurrentEnemy->TakeDamage(damage);
	}
}
