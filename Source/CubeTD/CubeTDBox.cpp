// Fill out your copyright notice in the Description page of Project Settings.

#include "CubeTDBox.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"


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

	ContainsStructure = false;

	Tower->Destroy();
}

void ACubeTDBox::BuildStructure()
{
	NeedsUpdate = true;

	Navigable = false;

	OnBoxPreUpdated.Broadcast(this);

	if (!Navigable) {
		auto World = GetWorld();
		ABasicTower* newTower = World->SpawnActor<ABasicTower>(ABasicTower::StaticClass());
		FVector SpawnScale = (this->GetActorScale3D());
		newTower->SetActorScale3D(SpawnScale);
		FVector SpawnLocation = (this)->GetActorLocation();
		newTower->SetActorLocation(SpawnLocation);
		Tower = newTower;
		ContainsStructure = true;
	}
}

void ACubeTDBox::UpgradeStructure()
{
	Tower->Destroy();
	auto World = GetWorld();
	AShootingTower* newTower = World->SpawnActor<AShootingTower>(AShootingTower::StaticClass());
	FVector SpawnScale = (this->GetActorScale3D());
	newTower->SetActorScale3D(SpawnScale);
	FVector SpawnLocation = (this)->GetActorLocation();
	newTower->SetActorLocation(SpawnLocation);
	Tower = Cast<ABasicTower>(newTower);
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

	if (ErrorMaterial)
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
		//TODO interfaz elegir opciones
		if (!Selected) {
			Selected = true;

			if (UsedMaterial)
				Mesh->SetMaterial(0, UsedMaterial);
			BuildStructure();
		}
		else if (ContainsStructure) {
			/*Selected = false;

			if (DefaultMaterial)
				Mesh->SetMaterial(0, DefaultMaterial);

			DestroyStructure();
			*/
			UpgradeStructure();
		}

	}
}

// Called every frame
void ACubeTDBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}