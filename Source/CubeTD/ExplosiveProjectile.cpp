// Fill out your copyright notice in the Description page of Project Settings.

#include "ExplosiveProjectile.h"


AExplosiveProjectile::AExplosiveProjectile() {
	ExplosionCollision= CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionCollision"));
}
void AExplosiveProjectile::Explode()
{
	PlayExplosion(ExplosionSystem);
	PlayExplosionSound(ExplosionSound);
	//Calcular daño area;
	if (this->IsValidLowLevel()) {
		Destroy();
	}
}

void AExplosiveProjectile::CalculateExplosion()
{
	TArray<AActor*> Enemigos;
	ExplosionCollision->GetOverlappingActors(Enemigos,TSubclassOf<ASplineFollower>());
	for (AActor* enemigo : Enemigos) {
		//Llamar evento takedamage del enemigo
	}
}


