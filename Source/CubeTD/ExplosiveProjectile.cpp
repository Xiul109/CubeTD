// Fill out your copyright notice in the Description page of Project Settings.

#include "ExplosiveProjectile.h"


AExplosiveProjectile::AExplosiveProjectile() {
	ExplosionCollision= CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionCollision"));
	ExplosionCollision->SetupAttachment(RootComponent);
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->SetupAttachment(ProjectileMesh);
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AExplosiveProjectile::OnOverlapBegin);
}
void AExplosiveProjectile::BeginExplode()
{
	CalculateExplosion();
	Explode();
}

void AExplosiveProjectile::CalculateExplosion()
{
	TArray<AActor*> Enemies;
	ExplosionCollision->GetOverlappingActors(Enemies, ABaseEnemy::StaticClass());
	for (AActor* enemy : Enemies) {
		class ABaseEnemy* CurrentEnemy = Cast<ABaseEnemy>(enemy);
		CurrentEnemy->TakeDamage(damage);
	}
}

void AExplosiveProjectile::OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &hitResult)
{
	class ABaseEnemy* Enemy = Cast<ABaseEnemy>(otherActor);

	if (Enemy != nullptr)
	{
		BeginExplode();
	}

	if (otherComp->GetName() == "GroundMesh")
	{
		Explode();
	}

}

