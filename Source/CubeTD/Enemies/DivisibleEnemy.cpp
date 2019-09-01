// Fill out your copyright notice in the Description page of Project Settings.

#include "DivisibleEnemy.h"

#include "Engine/World.h"


ADivisibleEnemy::ADivisibleEnemy() : SubdivisionsLeft(2), StatChangingRatio(0.5){
}


void ADivisibleEnemy::BeginPlay()
{
	Super::BeginPlay();

	OnDestroyed.AddDynamic(this, &ADivisibleEnemy::OnKilled);
}

void ADivisibleEnemy::OnKilled(AActor * Actor)
{
	if (SubdivisionsLeft > 0) {
		ADivisibleEnemy* NewEnemy1 = CreateDividedEnemy();
		ADivisibleEnemy* NewEnemy2 = CreateDividedEnemy();

		if (NewEnemy1 && NewEnemy2) {
			NewEnemy1->Speed = StatChangingRatio * Speed;
			NewEnemy2->Speed = (2 - StatChangingRatio) * Speed;
		}
		OnDivision.Broadcast(NewEnemy1, NewEnemy2);
	}
}

ADivisibleEnemy * ADivisibleEnemy::CreateDividedEnemy()
{
	auto World = GetWorld();

	if (World) {
		ADivisibleEnemy* NewEnemy = World->SpawnActor<ADivisibleEnemy>(GetClass());

		NewEnemy->MaxLife = NewEnemy->Life = Life * StatChangingRatio;
		NewEnemy->Speed = Speed* StatChangingRatio;

		NewEnemy->SubdivisionsLeft = SubdivisionsLeft - 1;

		NewEnemy->SetActorScale3D(StatChangingRatio*GetActorScale3D());

		NewEnemy->SplineRef = SplineRef;
		NewEnemy->PositionInSpline = PositionInSpline;

		return NewEnemy;
	}

	return nullptr;
}
