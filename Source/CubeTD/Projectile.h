// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseProjectile.h"
#include "Projectile.generated.h"

UCLASS()
class CUBETD_API AProjectile : public ABaseProjectile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

public:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &hitResult);
	
};


