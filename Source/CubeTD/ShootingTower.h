// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicTower.h"
#include "Projectile.h"
#include "ShootingTower.generated.h"


/**
 *
 */
UCLASS()
class CUBETD_API AShootingTower : public ABasicTower
{
	GENERATED_BODY()
public:
	AShootingTower();

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);

	
	UPROPERTY(EditDefaultsOnly, Category = "Turret Projectiles")
		TSubclassOf<class AProjectile> ProjectileClass;
};
