// Fill out your copyright notice in the Description page of Project Settings.

#include "CubeTDArena.h"

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

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(Arm, FAttachmentTransformRules::KeepRelativeTransform);
	Camera->bUsePawnControlRotation = false;

	//Main Mesh
	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));
	MainMesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ACubeTDArena::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ACubeTDArena::IsOuter(int i, int j, int k)
{
	int Size = Subdivisions + 2;
	bool iOuter = i == 0 || i == Size - 1;
	bool jOuter = j == 0 || j == Size - 1;
	bool kOuter = k == 0 || k == Size - 1;

	return iOuter || jOuter || kOuter;
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
		UChildActorComponent* AuxActor;
		auto Root = GetRootComponent();

		auto AuxActorInstance = NewObject<ACubeTDBox>(this, BoxClass);
		UStaticMeshComponent* AuxActorMesh = AuxActorInstance->Mesh;
		FVector Min, Max;
		AuxActorMesh->GetLocalBounds(Min, Max);
		AuxActorInstance->Destroy();

		//Falta Adaptar el tamaño al cubo interior
		FVector MeshDims = Max-Min;
		float MeshSize = MeshDims.GetMax();
		FVector IntDims = FVector(Size, Size, Size);
		FVector Origin = MeshDims * (IntDims - 1) / 2;

		for (int i = 0; i < Size; i++) {
			for (int j = 0; j < Size; j++) {
				for (int k = 0; k < Size; k++) {
					if (IsOuter(i, j, k)) {
						FName Name = FName(*FString::Printf(TEXT("Box_%d_%d_%d"), i, j, k));
						AuxActor = NewObject<UChildActorComponent>(this, Name);
						AuxActor->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

						AuxActor->CreationMethod = EComponentCreationMethod::UserConstructionScript;

						AuxActor->SetChildActorClass(BoxClass);

						FVector Offset = FVector(i * MeshSize, j * MeshSize, k * MeshSize) - Origin;
						AuxActor->AddRelativeLocation(Offset);
					}
				}
			}
		}
		RegisterAllComponents();
	}
}

