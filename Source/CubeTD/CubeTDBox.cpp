// Fill out your copyright notice in the Description page of Project Settings.

#include "CubeTDBox.h"
#include "CubeTDGameStateBase.h"

#include "Engine/World.h"
#include "Components/InputComponent.h"


// Sets default values
ACubeTDBox::ACubeTDBox() : Interactionable(true), Selected(false), NeedsUpdate(false)
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
	bool ret = true;
	if (Structure != nullptr) {
		ret = Structure->Navigable;
	}
	return ret;
}


void ACubeTDBox::DestroyStructure()
{
	NeedsUpdate = true;

	Structure->Destroy();

	Structure = nullptr;

	OnBoxPreUpdated.Broadcast(this);
}

void ACubeTDBox::BuildStructure(int option)
{
	TSubclassOf<ABasicStructure> ToSpawn;
	
	switch (option)
	{
	case 0:
		ToSpawn = BasicTowerClass;
		NeedsUpdate = true;
		break;
	case 1:
		ToSpawn = SlowTrapClass;
		break;
	case 2:
		ToSpawn = ExplosiveTrapClass;
		break;
	default:
		break;
	}

	auto World = GetWorld();
	if (World) {
		ABasicStructure* newStructure = World->SpawnActor<ABasicStructure>(ToSpawn);

		FVector SpawnScale = (this->GetActorScale3D());
		newStructure->SetActorScale3D(SpawnScale);
		FVector SpawnLocation = (this)->GetActorLocation();
		newStructure->SetActorLocation(SpawnLocation);
		Structure = newStructure;
	
		OnBoxPreUpdated.Broadcast(this);
	}
}

void ACubeTDBox::UpgradeStructure(int option)
{
	TSubclassOf<ABasicStructure> ToSpawn;
	switch (option)
	{
	case 0:
		ToSpawn = ShootingTowerClass;
		break;
	case 1:
		ToSpawn = AoeTowerClass;
		break;
	default:
		break;
	}
	
	auto World = GetWorld();
	if (World) {
		ABasicStructure* newStructure = World->SpawnActor<ABasicStructure>(ToSpawn);
		auto GameState = World->GetGameState<ACubeTDGameStateBase>();
		if (GameState->Resources >= newStructure->BaseCost)
		{
			Structure->Destroy();
			FVector SpawnScale = (this->GetActorScale3D());
			newStructure->SetActorScale3D(SpawnScale);
			FVector SpawnLocation = (this)->GetActorLocation();
			newStructure->SetActorLocation(SpawnLocation);
			Structure = Cast<ABasicStructure>(newStructure);

			Structure->Level = 1;
			GameState->Resources -= newStructure->BaseCost;

			OnTowerChange.Broadcast(this);
		}
		else {
			OnNotEnoughResources.Broadcast(this);
			newStructure->Destroy();
		}
	}
}
void ACubeTDBox::UpgradeTowerStats()
{
	auto GameState = GetWorld()->GetGameState<ACubeTDGameStateBase>();
	int UpgradeCost = Structure->CalcUpgradeCost();
	if (GameState->Resources >= UpgradeCost) {
		Structure->ProjectileDamage += Structure->ProjectileDamageUpgrade;
		Structure->Level += 1;
		GameState->Resources -= UpgradeCost;

		OnTowerChange.Broadcast(this);
	}
	else 
		OnNotEnoughResources.Broadcast(this);
	
}

void ACubeTDBox::UpdateBox()
{
	NeedsUpdate = false;

	auto World = GetWorld();
	if (World && Structure) {
		auto GameState = World->GetGameState<ACubeTDGameStateBase>();

		if (GameState->Resources >= Structure->BaseCost) {
			GameState->Resources -= Structure->BaseCost;
			OnTowerChange.Broadcast(this);
		}

		else {
			OnNotEnoughResources.Broadcast(this);
			CancelUpdate();
		}
	}
}

void ACubeTDBox::CancelUpdate()
{
	DestroyStructure();

	NeedsUpdate = false;

	Selected = false;

	if (ErrorMaterial)
		Mesh->SetMaterial(0, ErrorMaterial);

}

void ACubeTDBox::Disable()
{
	Interactionable = false;

	if(DisabledMaterial)
		Mesh->SetMaterial(0, DisabledMaterial);
}

void ACubeTDBox::Enable()
{
	Interactionable = true;

	if(Selected && UsedMaterial)
		Mesh->SetMaterial(0, UsedMaterial);
	else if (DefaultMaterial)
		Mesh->SetMaterial(0, DefaultMaterial);
}

void ACubeTDBox::Select()
{
	Selected = true;
	if (UsedMaterial)
		Mesh->SetMaterial(0, UsedMaterial);
	OnBoxSelected.Broadcast(this);
}

void ACubeTDBox::Deselect()
{
	Selected = false;
	if (DefaultMaterial)
		Mesh->SetMaterial(0, DefaultMaterial);
	OnBoxDeselected.Broadcast(this);
}

ABasicStructure * ACubeTDBox::GetStructure()
{
	return Structure;
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
			Select();
		}
		if (!IsValid(Structure) && BuildHudClass != nullptr) {
			CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), BuildHudClass);
			if (CurrentWidget != nullptr) {
				CurrentWidget->AddToViewport();
			}
		}
		else if (Structure && Structure->GetClass() == BasicTowerClass) {
			CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), UpgradeTowerHudClass);
			if (CurrentWidget != nullptr) {
				CurrentWidget->AddToViewport();
			}
		}
		else if (Structure && (Structure->GetClass() == ShootingTowerClass || Structure->GetClass() == AoeTowerClass)){
			CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), UpgradeTowerStatsHudClass);
			if (CurrentWidget != nullptr) {
				CurrentWidget->AddToViewport();
			}
					}
		else {
			CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), TrapStatsHudClass);
			if (CurrentWidget != nullptr) {
				CurrentWidget->AddToViewport();
			}
		}
	}

}

// Called every frame
void ACubeTDBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}