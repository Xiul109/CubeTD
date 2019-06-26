// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicTower.h"
#include "PhysicsEngine/PhysicsAsset.h"
#include "ConstructorHelpers.h"

// Sets default values
ABasicTower::ABasicTower()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));
	Mesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	// ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Game/Meshes/Sphere.Sphere'"));
	//Mesh->SetStaticMesh(MeshObj.Object);
}

// Called when the game starts or when spawned
void ABasicTower::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABasicTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}