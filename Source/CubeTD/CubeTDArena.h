// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CubeTDBox.h"
#include "ArenaData.h"
#include "SplineFollower.h"

#include "Structures/Spawner.h"
#include "Structures/Nexus.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "Engine/DataTable.h"

#include "GameFramework/Pawn.h"
#include "CubeTDArena.generated.h"


UCLASS()
class CUBETD_API ACubeTDArena : public APawn
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPathBlockedDelegate);

public:
	// Sets default values for this pawn's properties
	ACubeTDArena();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USpringArmComponent* Arm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MainMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USplineComponent* EnemiesPath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arena Settings")
	int Subdivisions;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arena Settings")
	TSubclassOf<ACubeTDBox> BoxClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arena Settings")
	TSubclassOf<ASplineFollower> SplineFollowerClass;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UArenaData* ArenaData;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arena Settings")
	FIntVector Origin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arena Settings")
	FIntVector Destination;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arena Settings")
	TSubclassOf<ASpawner> SpawnerClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arena Settings")
	TSubclassOf<ANexus> NexusClass;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arena Settings")
	TArray<UDataTable*> RoundsSpawnsData;

	//Delegates
	UPROPERTY(BlueprintAssignable)
	FPathBlockedDelegate OnPathBlocked;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual bool UpdatePath();

	TArray<ASplineFollower*> SplineFollowersSpawned;
	UPROPERTY()
	ACubeTDBox* SelectedBox;

	void SpawnSplineFollowers();
	void ClearSplineFollowers();

	//Functions for delegates
	UFUNCTION()
	void BoxPreUpdated(ACubeTDBox* Box);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	virtual void OnConstruction(const FTransform & Transform) override;

	UFUNCTION(BlueprintCallable)
	ACubeTDBox* GetSelectedBox() const;
};
