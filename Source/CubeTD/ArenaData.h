// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CubeTDBox.h"

#include "UObject/NoExportTypes.h"
#include "ArenaData.generated.h"

/**
 * 
 */

UENUM()
enum class EFaceEnum : int8
{
	X0   = -1,
	XMax = 1,
	Y0 = -2,
	YMax = 2,
	Z0 = -3,
	ZMax = 3
};

UCLASS()
class CUBETD_API UArenaData : public UObject
{
	GENERATED_BODY()
	
public:
	UArenaData();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FIntVector, ACubeTDBox*> Boxes;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Size;

	TArray<EFaceEnum> GetFacesOf(FIntVector Position) const;
	float GetNearestPointInFace(FIntVector Position, EFaceEnum Face, FIntVector &NearestPoint) const;
	TArray<ACubeTDBox*> GetAllNeighbours(FIntVector Position) const;
	float GetDistance(FIntVector V1, FIntVector V2) const;
	bool IsOuter(FIntVector Position) const;

	bool FindPath(FIntVector Origin, FIntVector End,TArray<FVector> &Path) const;
	TArray<FVector> PostProcessPath(TArray<FIntVector> Path) const;

	//////////////////////////////////////////////////////////////////////////
	// FGraphAStar: TGraph
	typedef FIntVector FNodeRef;

	int32 GetNeighbourCount(FNodeRef NodeRef) const;
	bool IsValidRef(FNodeRef NodeRef) const;
	FNodeRef GetNeighbour(const FNodeRef NodeRef, const int32 NeiIndex) const;
	//////////////////////////////////////////////////////////////////////////

private:
	TArray<FIntVector> AdjacentDisplacements;

	float ManhattanSize(FIntVector Vector) const;
};
