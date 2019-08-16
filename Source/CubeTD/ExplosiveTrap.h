// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTrap.h"
#include "ExplosiveTrap.generated.h"

/**
 * 
 */
UCLASS()
class CUBETD_API AExplosiveTrap : public ABaseTrap
{
	GENERATED_BODY()
public:
	AExplosiveTrap();
	float damage;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);
	
	UFUNCTION()
		void DamageEnemies();
};
