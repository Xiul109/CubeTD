// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicStructure.h"
#include "PhysicsEngine/PhysicsAsset.h"


// Sets default values
ABasicStructure::ABasicStructure()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));
	Mesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ABasicStructure::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicStructure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ABasicStructure::GetDamage()
{
	return damage;
}

FString ABasicStructure::GetName()
{
	return Name;
	
}

int ABasicStructure::CalcUpgradeCost()
{
	return UpgradeCost;
}

