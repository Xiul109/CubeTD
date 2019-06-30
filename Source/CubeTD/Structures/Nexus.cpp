// Fill out your copyright notice in the Description page of Project Settings.

#include "Nexus.h"



void ANexus::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);
	Navigable = true;
}
