// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "ExplosiveProjectile.generated.h"

/**
 * 
 */
UCLASS()
class CUBETD_API AExplosiveProjectile : public AProjectile
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AExplosiveProjectile();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		class USphereComponent* ExplosionCollision;

public:
	void Explode();
	void CalculateExplosion();

};
