// Fill out your copyright notice in the Description page of Project Settings.

#include "CubeTDBox.h"


// Sets default values
ACubeTDBox::ACubeTDBox() : Navigable(true), Interactionable(true), ContainsStructure(false), Selected(false), NeedsUpdate(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	//Main Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));
	Mesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	//Mouse events
	Mesh->OnBeginCursorOver.AddDynamic(this, &ACubeTDBox::OnBeginMouseOver);
	Mesh->OnEndCursorOver.AddDynamic(this, &ACubeTDBox::OnEndMouseOver);
	Mesh->OnClicked.AddDynamic(this, &ACubeTDBox::OnMouseClicked);
}

bool ACubeTDBox::IsNavigable() const
{
	return Navigable;
}


void ACubeTDBox::DestroyStructure()
{
	NeedsUpdate = true;

	Navigable = true;

	OnBoxPreUpdated.Broadcast(this);
}

void ACubeTDBox::BuildStructure()
{
	NeedsUpdate = true;

	Navigable = false;

	OnBoxPreUpdated.Broadcast(this);
}

void ACubeTDBox::UpgradeStructure()
{
}

void ACubeTDBox::UpdateBox()
{
	NeedsUpdate = false;
}

void ACubeTDBox::CancelUpdate()
{
	NeedsUpdate = false;

	Navigable = true;
	Selected = false;

	if(ErrorMaterial)
		Mesh->SetMaterial(0, ErrorMaterial);
}

// Called when the game starts or when spawned
void ACubeTDBox::BeginPlay()
{
	Super::BeginPlay();

	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	
}

void ACubeTDBox::OnBeginMouseOver(UPrimitiveComponent * TouchedComponent)
{
	if (HoverMaterial && Interactionable) {
		Mesh->SetMaterial(0, HoverMaterial);
	}
}

void ACubeTDBox::OnEndMouseOver(UPrimitiveComponent * TouchedComponent)
{
	if (Interactionable) {
		if (DefaultMaterial && !Selected) {
			Mesh->SetMaterial(0, DefaultMaterial);
		}
		else if (UsedMaterial && Selected) {
			Mesh->SetMaterial(0, UsedMaterial);
		}
	}
}

void ACubeTDBox::OnMouseClicked(UPrimitiveComponent * TouchedComponent, FKey key)
{
	if (Interactionable) {
		if (!Selected) {
			Selected = true;
			
			if (UsedMaterial) 
				Mesh->SetMaterial(0, UsedMaterial);

			BuildStructure();
		}
		else {
			Selected = false;
			
			if (DefaultMaterial) 
				Mesh->SetMaterial(0, DefaultMaterial);

			DestroyStructure();
		}
		
	}
}

// Called every frame
void ACubeTDBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

