// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProjectile.h"
#include "ExplosiveProjectile.generated.h"

/**
 * 
 */
UCLASS()
class CUBETD_API AExplosiveProjectile : public ABaseProjectile
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AExplosiveProjectile();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		class USphereComponent* ExplosionCollision;

public:
	void BeginExplode();
	void CalculateExplosion();
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &hitResult);


};
