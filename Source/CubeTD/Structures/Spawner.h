// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicStructure.h"
#include "Enemies/BaseEnemy.h"
#include "CubeTDRoundTableRow.h"
#include "Engine/DataTable.h"

#include "Spawner.generated.h"

/**
 * 
 */
UCLASS()
class CUBETD_API ASpawner : public ABasicStructure
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRoundFinishedDelegate);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LifeIncreasingRate = 1.05;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Round;

	UPROPERTY(BlueprintAssignable)
	FRoundFinishedDelegate OnRoundFinished;

protected:
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<FCubeTDRoundTableRow*> SpawnInfo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int EnemyCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int CurrentWave;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int SpawnsLeftsInCurrentWave;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABaseEnemy> EnemyClassToSpawn;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool Spawning;

	UPROPERTY()
		USplineComponent* SplineRef;

	FTimerHandle TimerHandle;


	void PrepareNextWave();
	UFUNCTION()
	void SpawnNextEnemy();
	UFUNCTION()
	virtual void OnEnemyDestroyed(AActor* Actor);

public:
	UFUNCTION(BlueprintCallable)
	void ActivateSpawner(UDataTable* NewSpawnInfo);

	void SetSplineRef(USplineComponent* Ref);

	virtual void OnConstruction(const FTransform & Transform) override;
};
