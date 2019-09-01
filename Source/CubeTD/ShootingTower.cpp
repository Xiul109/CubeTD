// Fill out your copyright notice in the Description page of Project Settings.

#include "ShootingTower.h"


AShootingTower::AShootingTower()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	CollisionComp->SetSphereRadius(240);
	CollisionComp->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
}

void AShootingTower::SetCooldown(float cd)
{
	CoolDown = cd;
}
void AShootingTower::SearchTarget()
{
	TArray<AActor*> Enemies;
	CollisionComp->GetOverlappingActors(Enemies, ABaseEnemy::StaticClass());
	if (Enemies.Num() > 0) {
		bool validEnemy = false;
		ABaseEnemy* tmp;
		while (!validEnemy && Enemies.Num()>0) {
			tmp = Cast<ABaseEnemy>(Enemies.Pop());
			if(!tmp->dead){
				validEnemy = true;
				Target = tmp;
			}
		}
	}
}
void AShootingTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AccumulatedDeltaTime += DeltaTime;
	if (AccumulatedDeltaTime >= CoolDown) {
		if (Target != nullptr) {
			if (!Target->dead) {
				auto World = GetWorld();
				if (World != NULL)
				{
					FVector currentPos = GetActorLocation();
					FRotator currentRot = FRotator(0, 0, 0);

					FActorSpawnParameters spawnParams;
					spawnParams.Owner = this;
					spawnParams.Instigator = Instigator;

					ABaseProjectile* FiredProjectile = World->SpawnActorDeferred<ABaseProjectile>(ProjectileClass, FTransform::Identity);

					if (FiredProjectile != nullptr)
					{
						FRotator meshRot = FiredProjectile->ProjectileMesh->GetComponentRotation();
						meshRot.Roll = 0.f;
						meshRot.Pitch = -90.f;
						meshRot.Yaw = 0.f;
						FiredProjectile->ProjectileMesh->SetRelativeRotation(meshRot);
						FiredProjectile->Target = Target;
						AccumulatedDeltaTime = 0.0f;

						FTransform params;
						params.SetLocation(currentPos);
						//params.SetRotation(currentRot);
						FiredProjectile->damage = this->ProjectileDamage;
						FiredProjectile->FinishSpawning(params);
					}

				}


			}
			else {
				//Clear target
				Target = nullptr;
			}
		}
		else {
			SearchTarget();
		}
	}
}
