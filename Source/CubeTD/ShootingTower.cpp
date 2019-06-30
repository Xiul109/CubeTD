// Fill out your copyright notice in the Description page of Project Settings.

#include "ShootingTower.h"


AShootingTower::AShootingTower()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	CollisionComp->SetSphereRadius(240);
	CollisionComp->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AShootingTower::BeginOverlap);
	
	CoolDown = 4.f;

}

void AShootingTower::BeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ASplineFollower* ActorCol= Cast<ASplineFollower>(OtherActor);
	if (ActorCol != nullptr) {
		Target = ActorCol;
	}
}
void AShootingTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AccumulatedDeltaTime += DeltaTime;
	if (Target != nullptr && AccumulatedDeltaTime >= CoolDown) {
		
				auto World = GetWorld();
				if (World != NULL)
				{
					FVector currentPos = GetActorLocation();
					FRotator currentRot = FRotator(0, 0, 0);

					FActorSpawnParameters spawnParams;
					spawnParams.Owner = this;
					spawnParams.Instigator = Instigator;

					//AProjectile* FiredProjectile = World->SpawnActor<AProjectile>(ProjectileClass, currentPos, currentRot, spawnParams);

					AProjectile* FiredProjectile = World->SpawnActor<AProjectile>(ProjectileClass);

					if (FiredProjectile != nullptr)
					{
						FRotator meshRot = FiredProjectile->ProjectileMesh->GetComponentRotation();
						meshRot.Roll = 0.f;
						meshRot.Pitch = -90.f;
						meshRot.Yaw = 0.f;
						FiredProjectile->ProjectileMesh->SetRelativeRotation(meshRot);
						FiredProjectile->Target = Target;
						AccumulatedDeltaTime = 0.0f;
					}
				}
			
		
		else {
			//Clear target
			Target = nullptr;
		}
	}
}
