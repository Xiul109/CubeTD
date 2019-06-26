// Fill out your copyright notice in the Description page of Project Settings.

#include "SplineFollower.h"
#include "PhysicsEngine/PhysicsAsset.h"


// Sets default values
ASplineFollower::ASplineFollower(): Speed(50), PositionInSpline(0)
{
	//Root Component
	auto Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	//Main Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));
	Mesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASplineFollower::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASplineFollower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float Movement = Speed * DeltaTime;
	PositionInSpline += Movement;

	if (PositionInSpline > SplineRef->GetSplineLength())
		PositionInSpline = 0;
	UpdateSplinePosition(PositionInSpline);
}



void ASplineFollower::UpdateSplinePosition(float NewPosition){
	if (SplineRef) {
		auto Transform = SplineRef->GetTransformAtDistanceAlongSpline(NewPosition, ESplineCoordinateSpace::World);
		SetActorLocation(Transform.GetLocation());
		SetActorRotation(Transform.GetRotation());

		//UE_LOG(LogTemp, Warning, TEXT("SplineDistance: %f"), distance);
	}
}
