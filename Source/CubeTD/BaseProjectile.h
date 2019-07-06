// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "Enemies/BaseEnemy.h"
#include "BaseProjectile.generated.h"

UCLASS()
class CUBETD_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		class UBoxComponent* CollisionComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		class UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		class UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FX")
		class UParticleSystem* ExplosionSystem;
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		class USoundCue* ExplosionSound;

	UPROPERTY(EditAnywhere)
		ABaseEnemy* Target;

	class UParticleSystemComponent* PlayExplosion(class UParticleSystem* explosion);
	class UAudioComponent* PlayExplosionSound(class USoundCue *sound);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FindTarget();
	void Explode();
	
};
