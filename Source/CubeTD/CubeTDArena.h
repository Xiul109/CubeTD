// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CubeTDBox.h"

#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "GameFramework/Pawn.h"
#include "CubeTDArena.generated.h"

UCLASS()
class CUBETD_API ACubeTDArena : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACubeTDArena();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USpringArmComponent* Arm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MainMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arena Settigns")
	int Subdivisions;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arena Settigns")
	TSubclassOf<ACubeTDBox> BoxClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool IsOuter(int i, int j, int k);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	virtual void OnConstruction(const FTransform & Transform) override;
};
