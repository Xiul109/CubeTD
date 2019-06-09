// Fill out your copyright notice in the Description page of Project Settings.

#include "CubeTDBox.h"


// Sets default values
ACubeTDBox::ACubeTDBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	auto Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	//Main Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));
	Mesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CollisionEnabledHasPhysics(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ACubeTDBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACubeTDBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

