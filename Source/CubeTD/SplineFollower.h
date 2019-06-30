// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SplineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "SplineFollower.generated.h"

UCLASS()
class CUBETD_API ASplineFollower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplineFollower();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Following")
	USplineComponent* SplineRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Following")
	float PositionInSpline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Following")
	float Speed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void UpdateSplinePosition(float NewPosition);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
