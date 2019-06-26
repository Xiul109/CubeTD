// Fill out your copyright notice in the Description page of Project Settings.

#include "ShootingTower.h"
#include "ConstructorHelpers.h"


AShootingTower::AShootingTower()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Game/Meshes/Shape_Cone.Shape_Cone'"));
	//Mesh->SetStaticMesh(MeshObj.Object);
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	const ConstructorHelpers::FClassFinder<AProjectile> BPProjectile(TEXT("Blueprint'/Game/Blueprints/ProjectileBP'"));
	ProjectileClass = BPProjectile.Class;

	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AShootingTower::BeginOverlap);
	
	CoolDown = 2.f;

}

void AShootingTower::BeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	class ASplineFollower* Enemy= Cast<ASplineFollower>(OtherActor);
	auto World = GetWorld();
	//Spawn proyectil
	if (Enemy!=nullptr && AccumulatedDeltaTime >= CoolDown)
	{
		if (World != NULL)
		{
			FVector currentPos = GetActorLocation();
			FRotator currentRot = FRotator(0, 0, 0);

			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			spawnParams.Instigator = Instigator;

			class AProjectile* FiredProjectile = World->SpawnActor<AProjectile>(ProjectileClass, currentPos, currentRot, spawnParams);

			if (FiredProjectile != nullptr)
			{
				// Set Mesh Rotation Offset. This rotation is based upon how your missile FBX was modeled.
				FRotator meshRot = FiredProjectile->ProjectileMesh->GetComponentRotation();
				meshRot.Roll = 0.f;
				meshRot.Pitch = -90.f;
				meshRot.Yaw = 0.f;
				FiredProjectile->ProjectileMesh->SetRelativeRotation(meshRot);
				FiredProjectile->Target=Enemy;
				AccumulatedDeltaTime = 0.0f;
			}
		}
	}
}
void AShootingTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AccumulatedDeltaTime += DeltaTime;
			
}