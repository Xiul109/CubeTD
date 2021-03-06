// Fill out your copyright notice in the Description page of Project Settings.

#include "Spawner.h"
#include "CubeTDGameStateBase.h"

#include "Engine/World.h"
#include "Engine/Public/TimerManager.h"


void ASpawner::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);
	Navigable = true;

	EnemyCount = 0;
	Round = -1;
	Spawning = false;
}

void ASpawner::PrepareNextWave()
{
	CurrentWave++;

	auto World = GetWorld();

	if (World) {
		World->GetTimerManager().ClearTimer(TimerHandle);
		if (CurrentWave < SpawnInfo.Num() && Spawning) {
			float TimeBetweenSpawns = SpawnInfo[CurrentWave]->TimeBetweenSpawns;
			World->GetTimerManager().SetTimer(TimerHandle, this, &ASpawner::SpawnNextEnemy, TimeBetweenSpawns, true);
			SpawnsLeftsInCurrentWave = SpawnInfo[CurrentWave]->NumberOfEnemies;
			EnemyClassToSpawn = SpawnInfo[CurrentWave]->EnemyClass;
		}
		else if (CurrentWave >= SpawnInfo.Num()) {
			Spawning = false;
		}
	}
}

void ASpawner::SpawnNextEnemy()
{
	auto World = GetWorld();

	if (World  && EnemyClassToSpawn) {
		auto Enemy = World->SpawnActor<ABaseEnemy>(EnemyClassToSpawn, GetActorTransform());
		Enemy->SplineRef = SplineRef;
		Enemy->Life += FMath::Pow(LifeIncreasingRate, Round);
		Enemy->OnDestroyed.AddDynamic(this, &ASpawner::OnEnemyDestroyed);

		if (EnemyClassToSpawn->IsChildOf(ADivisibleEnemy::StaticClass()))
			Cast<ADivisibleEnemy>(Enemy)->OnDivision.AddDynamic(this, &ASpawner::OnEnemyDivided);
	}

	SpawnsLeftsInCurrentWave--;
	if (SpawnsLeftsInCurrentWave <= 0) {
		PrepareNextWave();
	}
}

void ASpawner::OnEnemyDestroyed(AActor * Actor)
{
	EnemyCount--;
	ABaseEnemy* Enemy = Cast<ABaseEnemy>(Actor);

	if (Enemy && !Enemy->CancelReward) {
		OnEnemyDrop.Broadcast(Enemy->Reward);
		
		auto World = GetWorld();
		if (World) {
			auto GameState = World->GetGameState<ACubeTDGameStateBase>();
			GameState->Resources += Enemy->Reward;
		}
	}

	if (EnemyCount <= 0)
		OnRoundFinished.Broadcast();
}

void ASpawner::OnEnemyDivided(ADivisibleEnemy * Child1, ADivisibleEnemy * Child2)
{
	Child1->OnDivision.AddDynamic(this, &ASpawner::OnEnemyDivided);
	Child1->OnDestroyed.AddDynamic(this, &ASpawner::OnEnemyDestroyed);

	Child2->OnDivision.AddDynamic(this, &ASpawner::OnEnemyDivided);
	Child2->OnDestroyed.AddDynamic(this, &ASpawner::OnEnemyDestroyed);
	EnemyCount += 2;
}

void ASpawner::ActivateSpawner(UDataTable * NewSpawnInfo)
{
	if (!Spawning && EnemyCount<=0) {
		FString Context;
		SpawnInfo.Empty();
		NewSpawnInfo->GetAllRows<FCubeTDRoundTableRow>(Context, SpawnInfo);
		Round++;

		if (SpawnInfo.Num() > 0) {
			CurrentWave = -1;
			Spawning = true;

			EnemyCount = 0;
			for (auto Wave : SpawnInfo) {
				EnemyCount += Wave->NumberOfEnemies;
			}

			PrepareNextWave();
		}
	}
}

void ASpawner::SetSplineRef(USplineComponent * Ref)
{
	SplineRef = Ref;
}
