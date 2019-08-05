// Fill out your copyright notice in the Description page of Project Settings.

#include "CubeTDGameStateBase.h"
#include "CubeTDGameInstance.h"


ACubeTDGameStateBase::ACubeTDGameStateBase() : Resources(25) {
	StatsManager = NewObject<UStatsManager>();
}

void ACubeTDGameStateBase::BeginPlay()
{
	UCubeTDGameInstance* GI = Cast<UCubeTDGameInstance>(GetGameInstance());
	StatsManager->SetAchievementsManagerRef(GI->AchievementsManager);
}
