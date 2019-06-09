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
	Arm->bDoCollisionTest = false;

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

		//Mesh size of each Box
		auto AuxBoxInstance = NewObject<ACubeTDBox>(this, BoxClass);
		UStaticMeshComponent* AuxBoxMesh = AuxBoxInstance->Mesh;
		FVector Min, Max;
		AuxBoxMesh->GetLocalBounds(Min, Max);
		AuxBoxInstance->Destroy();
		FVector BoxDims = Max-Min;
		float BoxMeshSize = BoxDims.GetMax();

		//Obtaining the new Scale for the boxes
		MainMesh->GetLocalBounds(Min, Max);
		FVector MainMeshDims = Max - Min;
		float MainMeshSize = MainMeshDims.GetMax();
		float NewBoxScale = (MainMeshSize/Subdivisions)/BoxMeshSize;
		FVector RealBoxDims = BoxDims * NewBoxScale;
		float RealBoxSize = BoxMeshSize * NewBoxScale;

		//Getting the origin point to place each actor correctly
		FVector ArenaDims = FVector(Size);
		FVector Origin = RealBoxDims * (ArenaDims - 1) / 2;

		for (int i = 0; i < Size; i++) {
			for (int j = 0; j < Size; j++) {
				for (int k = 0; k < Size; k++) {
					if (IsOuter(i, j, k)) {
						FName Name = FName(*FString::Printf(TEXT("Box_%d_%d_%d"), i, j, k));
						AuxActor = NewObject<UChildActorComponent>(this, Name);
						AuxActor->SetRelativeScale3D(FVector(NewBoxScale));
						AuxActor->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

						AuxActor->CreationMethod = EComponentCreationMethod::UserConstructionScript;

						AuxActor->SetChildActorClass(BoxClass);

						FVector Offset = FVector(i * RealBoxSize, j * RealBoxSize, k * RealBoxSize) - Origin;
						AuxActor->AddRelativeLocation(Offset);
					}
				}
			}
		}
		RegisterAllComponents();
	}
}

