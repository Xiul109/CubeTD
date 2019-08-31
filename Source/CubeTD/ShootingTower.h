// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicTower.h"
#include "BaseProjectile.h"
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
	
	UPROPERTY(EditDefaultsOnly, Category = "Turret Projectiles")
		TSubclassOf<class ABaseProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere)
		ABaseEnemy* Target;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Cd")
	float CoolDown;
	float AccumulatedDeltaTime;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

	UFUNCTION(BlueprintCallable)
		void SetCooldown(float cd);

	UFUNCTION()
		void SearchTarget();
};
