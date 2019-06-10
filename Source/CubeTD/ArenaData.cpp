// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaData.h"

UArenaData::UArenaData() {
	for (int dim=0; dim < 3; dim++) {
		for (int Displacement : {-1, 1}) {
			FVector AuxVector = FVector(0);
			AuxVector[dim] = Displacement;
			AdjacentDisplacements.Add(AuxVector);
		}
	}
}

TArray<ACubeTDBox*> UArenaData::GetAdjacentBoxesTo(FVector Position)
{
	TArray<ACubeTDBox*> AdjacentBoxes;
	
	for (FVector Displacement : AdjacentDisplacements) {
		FVector PosibleAdjPosition = Position + Displacement;
		if (Boxes.Contains(PosibleAdjPosition))
			AdjacentBoxes.Add(*Boxes.Find(PosibleAdjPosition));
	}

	return AdjacentBoxes;
}

float UArenaData::GetDistance(FVector V1, FVector V2)
{

	if (AreInOppositeFace(V1,V2)) {
		//Find nearest Point in face border to V2
		TTuple<bool, FVector> asd;
	}
	else {
		return ManhattanSize(V2 - V1);
	}
}


bool UArenaData::AreInOppositeFace(FVector V1, FVector V2)
{
	for (int dim = 0; dim < 3; dim++) 
		if ((V1[dim] == 0 && V2[dim] == Size - 1) || (V1[dim] == Size - 1 && V2[dim] == 0))
			return true;
	
	return false;
}



float UArenaData::ManhattanSize(FVector Vector)
{
	float MSize = 0;
	for (int dim = 0; dim < 3; dim++)
		MSize += abs(Vector[dim]);
	
	return MSize;
}
