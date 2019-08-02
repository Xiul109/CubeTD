// Fill out your copyright notice in the Description page of Project Settings.

#include "StatsManager.h"



void UStatsManager::SetAchievementsManagerRef(UAchievementsManager * ref)
{
	AchievementsManagerRef = ref;
}

void UStatsManager::UpdateAchievementsManager()
{
	if (AchievementsManagerRef)
		AchievementsManagerRef->UpdateAchievements(CurrentGameStats);
}

void UStatsManager::UpdateEnemiesKilled()
{
	CurrentGameStats.EnemiesKilled++;
	UpdateAchievementsManager();
}

void UStatsManager::UpdateTowersBuilt()
{
	CurrentGameStats.TowersBuilt++;
	UpdateAchievementsManager();
}

void UStatsManager::UpdateResourcesGained(int Resources)
{
	CurrentGameStats.ResourcesGained = Resources;
	UpdateAchievementsManager();
}

void UStatsManager::UpdateMazeLenght(int NewLenght)
{
	CurrentGameStats.MazeLenght = NewLenght;
	UpdateAchievementsManager();
}

void UStatsManager::UpdateRoundsWon()
{
	CurrentGameStats.RoundsWon++;
	UpdateAchievementsManager();
}
