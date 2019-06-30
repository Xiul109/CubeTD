// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicStructure.h"
#include "Spawner.generated.h"

/**
 * 
 */
UCLASS()
class CUBETD_API ASpawner : public ABasicStructure
{
	GENERATED_BODY()

public:
	virtual void OnConstruction(const FTransform & Transform) override;

};
