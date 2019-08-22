// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicStructure.h"
#include "Engine.h"
#include "Enemies/BaseEnemy.h"
#include "BaseTrap.generated.h"

UCLASS()
class CUBETD_API ABaseTrap : public ABasicStructure
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseTrap();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Collision")
		class UBoxComponent* CollisionComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
		float Durability;
	float AccumulatedDeltaTime;
	bool Activated;

};
