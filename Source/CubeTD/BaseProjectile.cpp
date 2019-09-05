// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseProjectile.h"


// Sets default values
ABaseProjectile::ABaseProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	auto Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));

	ProjectileMesh->SetupAttachment(RootComponent);

	// Construct Projectile Movement Component
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = RootComponent;
	ProjectileMovement->InitialSpeed = 300.f;
	ProjectileMovement->MaxSpeed = 500.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bInitialVelocityInLocalSpace = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->bIsHomingProjectile = false;
	ProjectileMovement->HomingAccelerationMagnitude = 0.f;
	ProjectileMovement->Velocity = FVector(0, 0, 0);
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	FindTarget();
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FindTarget();
}

void ABaseProjectile::FindTarget() {
	if (Target != NULL && !Target->dead)
	{
			FVector wantedDir = (Target->GetActorLocation() - GetActorLocation());
			wantedDir += Target->GetVelocity() * wantedDir.Size() / 200.f;
			ProjectileMovement->Velocity = wantedDir * 200.f;
			ProjectileMovement->Velocity = ProjectileMovement->Velocity.GetSafeNormal() * 200.f;
			ProjectileMovement->UpdateComponentVelocity();
		
	}
	else {
		Explode();
	}
}
class UParticleSystemComponent* ABaseProjectile::PlayExplosion(class UParticleSystem* explosion)
{
	class UParticleSystemComponent* retVal = NULL;

	if (explosion)
	{
		class UWorld* const world = GetWorld();

		if (world)
		{
			FVector myPos = GetActorLocation();
			FRotator myRot = GetActorRotation();

			retVal = UGameplayStatics::SpawnEmitterAtLocation(world, explosion, myPos, myRot, true);
		}
	}

	return retVal;
}
void ABaseProjectile::Explode()
{
	if (ExplosionSystem != nullptr) {
		PlayExplosion(ExplosionSystem);
	}
	PlayExplosionSound(ExplosionSound);
	if (this->IsValidLowLevel()) {
		Destroy();
	}
}
class UAudioComponent* ABaseProjectile::PlayExplosionSound(class USoundCue *sound)
{
	class UAudioComponent* retVal = NULL;

	if (sound)
		retVal = UGameplayStatics::SpawnSoundAttached(sound, this->GetRootComponent());

	return retVal;
}