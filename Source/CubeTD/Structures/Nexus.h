// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicStructure.h"
#include "Nexus.generated.h"

/**
 * 
 */
UCLASS()
class CUBETD_API ANexus : public ABasicStructure
{
	GENERATED_BODY()
	
public:
	virtual void OnConstruction(const FTransform & Transform) override;
	
};
