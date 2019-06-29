// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "PhysicsEngine/PhysicsAsset.h"
#include "ConstructorHelpers.h"




// Sets default values
AProjectile::AProjectile()
{
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	//const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Game/Meshes/Sphere.Sphere'"));
	//ProjectileMesh->SetStaticMesh(MeshObj.Object);
	ProjectileMesh->SetupAttachment(RootComponent);

	// Construct Projectile Movement Component
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 300.f;
	ProjectileMovement->MaxSpeed = 500.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bInitialVelocityInLocalSpace = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->bIsHomingProjectile = false;
	ProjectileMovement->HomingAccelerationMagnitude = 0.f;
	ProjectileMovement->Velocity = FVector(0, 0, 0);

	// Bind our OnOverlapBegin Event
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	FindTarget();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FindTarget();
}

void AProjectile::FindTarget() {
	if (Target != NULL)
	{
		if (Target->IsValidLowLevel())
		{
			FVector wantedDir = (Target->GetActorLocation() - GetActorLocation());
			ProjectileMovement->Velocity = wantedDir;
			ProjectileMovement->UpdateComponentVelocity();
		}
	}
	else {
		Explode();
	}
}


void AProjectile::Explode()
{
	PlayExplosion(ExplosionSystem);
	PlayExplosionSound(ExplosionSound);
	if (this->IsValidLowLevel()) {
		Destroy();
	}
}

class UParticleSystemComponent* AProjectile::PlayExplosion(class UParticleSystem* explosion)
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
class UAudioComponent* AProjectile::PlayExplosionSound(class USoundCue *sound)
{
	class UAudioComponent* retVal = NULL;

	if (sound)
		retVal = UGameplayStatics::SpawnSoundAttached(sound, this->GetRootComponent());

	return retVal;
}

void AProjectile::OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &hitResult)
{
	class ASplineFollower* Enemy = Cast<ASplineFollower>(otherActor);
	//class ACubeTDArena* GroundActor = Cast<ACubeTDArena>(otherActor);

	if (Enemy != nullptr)
	{
		Explode();
	}

	/*if (GroundActor != nullptr)
	{
		Explode();
	}*/
	
}

