// Fill out your copyright notice in the Description page of Project Settings.

#include "CubeTDArena.h"
#include "CubeTDGameInstance.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"

// Sets default values
ACubeTDArena::ACubeTDArena(): Subdivisions(3)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	//Camera
	Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	Arm->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	Arm->bUsePawnControlRotation = true;
	Arm->TargetArmLength = 300;
	Arm->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(Arm, FAttachmentTransformRules::KeepRelativeTransform);
	Camera->bUsePawnControlRotation = false;

	//Main Mesh
	GroundMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GroundMesh"));
	GroundMesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ACubeTDArena::BeginPlay()
{
	Super::BeginPlay();
	UpdatePath();
	
	SpawnSplineFollowers();

	//Prepare Origin and End Boxes
	ACubeTDBox* OriginBox = *ArenaData->Boxes.Find(Origin);
	ACubeTDBox* DestinationBox = *ArenaData->Boxes.Find(Destination);
	OriginBox->Disable(); DestinationBox->Disable();

	auto World = GetWorld();
	if (World) {
		if (SpawnerClass) {
			OriginBox->Structure = Spawner = World->SpawnActor<ASpawner>(SpawnerClass, OriginBox->GetActorTransform());
			Spawner->SetSplineRef(EnemiesPath);
			Spawner->OnRoundFinished.AddDynamic(this, &ACubeTDArena::RoundFinished);
		}
		if(NexusClass)
			DestinationBox->Structure = Nexus	= World->SpawnActor<ANexus>(NexusClass, DestinationBox->GetActorTransform());
	}

	//Box Update Delegates
	for (auto Box : ArenaData->Boxes) {
		Box.Value->OnBoxPreUpdated.AddDynamic(this, &ACubeTDArena::BoxPreUpdated);
		Box.Value->OnBoxSelected.AddDynamic(this, &ACubeTDArena::BoxSelected);
		Box.Value->OnBoxDeselected.AddDynamic(this, &ACubeTDArena::BoxDeselected);
		Box.Value->OnTowerChange.AddDynamic(this, &ACubeTDArena::TowerChanged);
		Box.Value->OnNotEnoughResources.AddDynamic(this, &ACubeTDArena::NotEnoughtResources);
	}

	auto GameInstance = World->GetGameInstance<UCubeTDGameInstance>();
	ABasicStructure* tmp = World->SpawnActorDeferred<ABasicStructure>(OriginBox->ShootingTowerClass, FTransform::Identity);
	GameInstance->ShootingTCost = tmp->BaseCost;
	tmp->Destroy();
	tmp = World->SpawnActorDeferred<ABasicStructure>(OriginBox->AoeTowerClass, FTransform::Identity);
	GameInstance->AoETCost = tmp->BaseCost;
	tmp->Destroy();
	tmp = World->SpawnActorDeferred<ABasicStructure>(OriginBox->SlowTrapClass, FTransform::Identity);
	GameInstance->SlowTCost = tmp->BaseCost;
	tmp->Destroy();
	tmp = World->SpawnActorDeferred<ABasicStructure>(OriginBox->ExplosiveTrapClass, FTransform::Identity);
	GameInstance->ExplTCost = tmp->BaseCost;
	tmp->Destroy();
	tmp = World->SpawnActorDeferred<ABasicStructure>(OriginBox->BasicTowerClass, FTransform::Identity);
	GameInstance->BaseTCost = tmp->BaseCost;
	tmp->Destroy();
	tmp = nullptr;
}

bool ACubeTDArena::UpdatePath()
{
	if (EnemiesPath)
		EnemiesPath->UnregisterComponent();

	if (ArenaData) {
		if (ArenaData->IsOuter(Origin) && ArenaData->IsOuter(Destination)) {
			TArray<FVector> PathPoints;
			if (ArenaData->FindPath(Origin, Destination, PathPoints)) {
				EnemiesPath = NewObject<USplineComponent>(this);
				EnemiesPath->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
				EnemiesPath->RegisterComponent();
				
				EnemiesPath->RemoveSplinePoint(0);
				EnemiesPath->RemoveSplinePoint(0);
				for (FVector Point : PathPoints) {
					EnemiesPath->AddSplinePoint(Point,ESplineCoordinateSpace::World);
				}
				EnemiesPath->bDrawDebug = true;

				if(Spawner)
					Spawner->SetSplineRef(EnemiesPath);

				OnPathUpdated.Broadcast();

				return true;
			}
		}
	}
	return false;
}

void ACubeTDArena::SpawnSplineFollowers()
{
	auto World = GetWorld();
	if (SplineFollowerClass && World && EnemiesPath && ArenaData) {
		int FollowersToSpawn = EnemiesPath->GetNumberOfSplinePoints();
		float DistanceIncrement = EnemiesPath->GetSplineLength() / FollowersToSpawn;
		for (int i = 0; i < FollowersToSpawn; i++) {
			ASplineFollower* SplineFollower = World->SpawnActor<ASplineFollower>(SplineFollowerClass);
			SplineFollower->SplineRef = EnemiesPath;
			SplineFollower->PositionInSpline = i * DistanceIncrement;
			
			FVector SpawnScale = (*ArenaData->Boxes.Find(FIntVector(0)))->GetActorScale3D();
			SplineFollower->SetActorScale3D(SpawnScale);


			SplineFollowersSpawned.Add(SplineFollower);
		}		
	}
}

void ACubeTDArena::ClearSplineFollowers()
{
	for (ASplineFollower* Follower : SplineFollowersSpawned) {
		Follower->Destroy();
	}
	SplineFollowersSpawned.Empty();
}

void ACubeTDArena::BoxPreUpdated(ACubeTDBox* Box)
{
	if (UpdatePath()) {
		ClearSplineFollowers();
		SpawnSplineFollowers();
		Box->UpdateBox();
	}
	else {
		OnPathBlocked.Broadcast();
		Box->CancelUpdate();
	}
}

void ACubeTDArena::BoxSelected(ACubeTDBox * Box)
{
	if (Box != SelectedBox) {
		if(SelectedBox)
			SelectedBox->Deselect();
		SelectedBox = Box;
	}
}

void ACubeTDArena::BoxDeselected(ACubeTDBox * Box)
{
	if (SelectedBox == Box)
		SelectedBox = nullptr;
}

void ACubeTDArena::TowerChanged(ACubeTDBox * Box)
{
	OnTowerBuiltOrUpgraded.Broadcast();
}

void ACubeTDArena::RoundFinished()
{
	OnRoundFinished.Broadcast();
	SetBoxesEnabled(true);
}

void ACubeTDArena::NotEnoughtResources(ACubeTDBox * Box)
{
	OnNotEnoughResources.Broadcast();
}


// Called every frame
void ACubeTDArena::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

// Called to bind functionality to input
void ACubeTDArena::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

}

void ACubeTDArena::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);

	if (BoxClass) {
		int Size = Subdivisions + 2;

		//Init Arena Data
		ArenaData = NewObject<UArenaData>(this);
		ArenaData->Size = Size;

		//Mesh size of each Box
		auto AuxBoxInstance = NewObject<ACubeTDBox>(this, BoxClass);
		UStaticMeshComponent* AuxBoxMesh = AuxBoxInstance->Mesh;
		FVector Min, Max;
		AuxBoxMesh->GetLocalBounds(Min, Max);
		AuxBoxInstance->Destroy();
		FVector BoxDims = Max-Min;
		float BoxMeshSize = BoxDims.GetMax();

		//Obtaining the new Scale for the boxes
		GroundMesh->GetLocalBounds(Min, Max);
		FVector MainMeshDims = Max - Min;
		float MainMeshSize = MainMeshDims.GetMax();
		float BoxScale = (MainMeshSize/Subdivisions)/BoxMeshSize;
		FVector RealBoxDims = BoxDims * BoxScale;
		float RealBoxSize = BoxMeshSize * BoxScale;

		//Getting the origin point to place each actor correctly
		FVector ArenaDims = FVector(Size);
		FVector Origin = RealBoxDims * (ArenaDims - 1) / 2;

		for (int i = 0; i < Size; i++) {
			for (int j = 0; j < Size; j++) {
				for (int k = 0; k < Size; k++) {
					FIntVector Position = FIntVector(i, j, k);
					if (ArenaData->IsOuter(Position)) {
						//Creating and attaching the object
						FName Name = FName(*FString::Printf(TEXT("Box_%d_%d_%d"), i, j, k));
						UChildActorComponent* AuxActor = NewObject<UChildActorComponent>(this, Name);
						AuxActor->AttachToComponent(GroundMesh, FAttachmentTransformRules::KeepRelativeTransform);

						//Creating the Box itself
						AuxActor->CreationMethod = EComponentCreationMethod::UserConstructionScript;
						AuxActor->SetChildActorClass(BoxClass);
						AuxActor->CreateChildActor();

						//Moving and resizing the box
						FVector Offset = FVector(Position)*RealBoxSize - Origin;
						AuxActor->AddRelativeLocation(Offset);
						AuxActor->SetRelativeScale3D(FVector(BoxScale));

						//Inluding the object into the arena
						ACubeTDBox* AuxBox = Cast<ACubeTDBox>(AuxActor->GetChildActor());
						AuxBox->Position = Position;
						ArenaData->Boxes.Add(Position, AuxBox);
					}
				}
			}
		}
		RegisterAllComponents();
	}
}

ACubeTDBox * ACubeTDArena::GetSelectedBox() const
{
	return SelectedBox;
}

void ACubeTDArena::StartNewRound()
{	
	if (SelectedBox != nullptr) {
		SelectedBox->Deselect();
	}
	if (Spawner) {
		Spawner->ActivateSpawner(GetNextRoundInfo());
		SetBoxesEnabled(false);
	}
}

void ACubeTDArena::SetBoxesEnabled(bool Enabled)
{
	for (auto Pair : ArenaData->Boxes) {
		if (Pair.Key != Origin && Pair.Key != Destination){
			if (Enabled)
				Pair.Value->Enable();
			else
				Pair.Value->Disable();
		}
	}
}

bool ACubeTDArena::UsePowerUp(float cost)
{
	bool ret=false;
	auto World = GetWorld();
	auto GameState = World->GetGameState<ACubeTDGameStateBase>();
	if (GameState->Resources >= cost) {
		GameState->Resources -= cost;
		ret = true;
	}
	return ret;
}

UDataTable * ACubeTDArena::GetNextRoundInfo() const
{
	int NextRoundSpawns = (Spawner->Round + 1) % RoundsSpawnsData.Num();
	return RoundsSpawnsData[NextRoundSpawns];
}

