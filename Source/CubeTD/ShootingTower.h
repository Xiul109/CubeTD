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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Collision")
		class USphereComponent* CollisionComp;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);

	
	UPROPERTY(EditDefaultsOnly, Category = "Turret Projectiles")
		TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere)
		ASplineFollower* Target;
	
	float CoolDown;
	float AccumulatedDeltaTime;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
