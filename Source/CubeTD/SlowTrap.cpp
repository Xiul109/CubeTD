// Fill out your copyright notice in the Description page of Project Settings.

#include "SlowTrap.h"


ASlowTrap::ASlowTrap()
{
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ASlowTrap::BeginOverlap);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this, &ASlowTrap::OverlapEnd);
}


void ASlowTrap::Tick(float DeltaTime)
{
	if (Activated) {
		AccumulatedDeltaTime += DeltaTime;
		if (AccumulatedDeltaTime >= Durability) {
			Destroy();
		}
	}
}

void ASlowTrap::BeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
	ABaseEnemy* ActorCol = Cast<ABaseEnemy>(OtherActor);
	if (ActorCol != nullptr) {
		Activated = true;
		ActorCol->CustomTimeDilation = 0.5;
	}
}

void ASlowTrap::OverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) 
{
	ABaseEnemy* ActorCol = Cast<ABaseEnemy>(OtherActor);
	if (ActorCol != nullptr) {
		ActorCol->CustomTimeDilation = 1;
	}
}
