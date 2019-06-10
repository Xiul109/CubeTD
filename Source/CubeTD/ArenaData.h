// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CubeTDBox.h"

#include "UObject/NoExportTypes.h"
#include "ArenaData.generated.h"

/**
 * 
 */
UCLASS()
class CUBETD_API UArenaData : public UObject
{
	GENERATED_BODY()
	
public:
	UArenaData();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FVector, ACubeTDBox*> Boxes;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Size;

	TArray<ACubeTDBox*> GetAdjacentBoxesTo(FVector Position);
	float GetDistance(FVector V1, FVector V2);

private:
	TArray<FVector> AdjacentDisplacements;

	bool AreInOppositeFace(FVector V1, FVector V2);

	float ManhattanSize(FVector Vector);
};
