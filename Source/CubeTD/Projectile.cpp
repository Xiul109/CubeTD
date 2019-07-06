// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "PhysicsEngine/PhysicsAsset.h"




// Sets default values
AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->SetupAttachment(ProjectileMesh);
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
}

// Called when the game starts or when spawned


void AProjectile::OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &hitResult)
{
	class ABaseEnemy* Enemy = Cast<ABaseEnemy>(otherActor);
	
	if (Enemy != nullptr)
	{
		Explode();
	}

	if (otherComp->GetName()=="GroundMesh")
	{
		Explode();
	}
	
}

