// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaData.h"
#include "AIModule/Public/GraphAStar.h"

UArenaData::UArenaData() {
	for (int dim=0; dim < 3; dim++) {
		for (int Displacement : {-1, 1}) {
			FIntVector AuxVector = FIntVector(0);
			AuxVector[dim] = Displacement;
			AdjacentDisplacements.Add(AuxVector);
		}
	}
}

TArray<EFaceEnum> UArenaData::GetFacesOf(FIntVector Position) const
{
	TArray<EFaceEnum> Faces;
	for (uint8 dim = 1; dim <= 3; dim++) {
		if (Position[dim-1] == 0)
			Faces.Add(EFaceEnum(-dim));
		else if(Position[dim-1] == Size-1)
			Faces.Add(EFaceEnum(dim));
	}
	return Faces;
}

float UArenaData::GetNearestPointInFace(FIntVector Position, EFaceEnum Face, FIntVector & NearestPoint) const
{
	FIntVector BestPoint;
	float BestDistance = Size * Size *Size, Distance;
	for (int dim = 0; dim < 3; dim++) {
		if (dim != FMath::Abs((int)Face-1)) {
			for (int value : {0, Size - 1}) {
				Distance = FMath::Abs(value - Position[dim]);
				if (Distance < BestDistance) {
					BestDistance = Distance;
					BestPoint = Position;
					BestPoint[dim] = value;
				}
			}
		}
	}
	NearestPoint = BestPoint;
	return BestDistance;
}

TArray<ACubeTDBox*> UArenaData::GetAllNeighbours(FIntVector Position) const
{
	TArray<ACubeTDBox*> Neighbours;
	
	for (FIntVector Displacement : AdjacentDisplacements) {
		FIntVector PosibleAdjPosition = Position + Displacement;
		if (Boxes.Contains(PosibleAdjPosition)) 
			Neighbours.Add(*Boxes.Find(PosibleAdjPosition));	
	}

	return Neighbours;
}

float UArenaData::GetDistance(FIntVector V1, FIntVector V2) const
{
	auto FacesV1 = GetFacesOf(V1);
	auto FacesV2 = GetFacesOf(V2);
	//When points are in oposite faces
	if (FacesV1.Num() == 1 && FacesV2.Num() == 1 && (int)FacesV1[0] == -(int)FacesV2[0]) {
		//Find nearest Point in face border to V2
		FIntVector AuxPoint;
		float PartialDistance = GetNearestPointInFace(V2, FacesV2[0], AuxPoint);
		return PartialDistance + ManhattanSize(AuxPoint - V1);
	}
	else {
		return ManhattanSize(V2 - V1);
	}
}

bool UArenaData::IsOuter(FIntVector Position) const
{
	int i = Position.X, j = Position.Y, k = Position.Z;

	bool iOuter = i == 0 || i == Size - 1;
	bool jOuter = j == 0 || j == Size - 1;
	bool kOuter = k == 0 || k == Size - 1;

	return iOuter || jOuter || kOuter;
}

struct FArenaPathFilter{

	FArenaPathFilter(const UArenaData& InArenaRef) : ArenaRef(InArenaRef) {}

	float GetHeuristicScale() const
	{
		return 1.0f;
	}

	float GetHeuristicCost(const FIntVector StartNodeRef, const FIntVector EndNodeRef) const
	{
		return GetTraversalCost(StartNodeRef, EndNodeRef);
	}

	float GetTraversalCost(const FIntVector StartNodeRef, const FIntVector EndNodeRef) const
	{
		return ArenaRef.GetDistance(StartNodeRef, EndNodeRef);
	}

	bool IsTraversalAllowed(const FIntVector NodeA, const FIntVector NodeB) const
	{
		return ArenaRef.Boxes[NodeB]->IsNavigable();
	}

	bool WantsPartialSolution() const
	{
		return false;
	}

protected:
	const UArenaData& ArenaRef;
};

bool UArenaData::FindPath(FIntVector Origin, FIntVector End, TArray<FVector>& Path) const
{
	TArray<FIntVector> PathIndices;
	FGraphAStar<UArenaData> Pathfinder(*this);
	Pathfinder.FindPath(Origin, End, FArenaPathFilter(*this), PathIndices);

	if (PathIndices.Num() > 0) {
		Path = PostProcessPath(PathIndices);
		return true;
	}

	return false;
}

TArray<FVector> UArenaData::PostProcessPath(TArray<FIntVector> Path) const
{
	TArray<FVector> ProcessedPath;
	for (FIntVector Index : Path) {
		ProcessedPath.Add(Boxes[Index]->GetActorLocation());
	}
	return ProcessedPath;
}

int32 UArenaData::GetNeighbourCount(FIntVector NodeRef) const
{
	return GetAllNeighbours(NodeRef).Num();
}

bool UArenaData::IsValidRef(FIntVector NodeRef) const
{
	return IsOuter(NodeRef);
}

FIntVector UArenaData::GetNeighbour(const FIntVector NodeRef, const int32 NeiIndex) const
{
	return GetAllNeighbours(NodeRef)[NeiIndex]->Position;
}


float UArenaData::ManhattanSize(FIntVector Vector) const
{
	float MSize = 0;
	for (int dim = 0; dim < 3; dim++)
		MSize += abs(Vector[dim]);
	
	return MSize;
}
