// Fill out your copyright notice in the Description page of Project Settings.

#include "AchievementsManager.h"

#include "Kismet/GameplayStatics.h"
#include "CubeTDSaveGame.h"

// Achievements Names													//Achievements Thresholds values
constexpr auto ENEMIES1NAME = "Kill your first enemy";					constexpr int ENEMIES1NUM = 1;
constexpr auto ENEMIES2NAME = "Kill 50 enemies";						constexpr int ENEMIES2NUM = 50;
constexpr auto ENEMIES3NAME = "Kill 500 enemies";						constexpr int ENEMIES3NUM = 500;
constexpr auto ENEMIES4NAME = "Kill 5000 enemies";						constexpr int ENEMIES4NUM = 5000;

constexpr auto TOWERS1NAME = "Build your first tower";					constexpr int TOWERS1NUM = 1;
constexpr auto TOWERS2NAME = "Build 10 towers";							constexpr int TOWERS2NUM = 10;
constexpr auto TOWERS3NAME = "Build 100 towers";						constexpr int TOWERS3NUM = 100;
constexpr auto TOWERS4NAME = "Build 1000 towers";						constexpr int TOWERS4NUM = 1000;

constexpr auto RESOURCES1NAME = "Have 100 Resources";					constexpr int RESOURCES1NUM = 100;
constexpr auto RESOURCES2NAME = "Have 1000 Resources";					constexpr int RESOURCES2NUM = 1000;
constexpr auto RESOURCES3NAME = "Have 10000 Resources";					constexpr int RESOURCES3NUM = 10000;

constexpr auto ROUNDS1NAME = "Win your first round";					constexpr int ROUNDS1NUM = 1;
constexpr auto ROUNDS2NAME = "Win 5 rounds in a row";					constexpr int ROUNDS2NUM = 5;
constexpr auto ROUNDS3NAME = "Win 25 rounds in a row";					constexpr int ROUNDS3NUM = 25;
constexpr auto ROUNDS4NAME = "Win 50 rounds in a row";					constexpr int ROUNDS4NUM = 50;

constexpr auto MAZE1NAME = "Build a maze with a lenght of 45 boxes";	constexpr int MAZE1NUM = 45;

//Type Achievement IDs
constexpr uint8 ALL = 0, ENEMIES = 1, TOWERS = 2, RESOURCES = 3, ROUNDS = 4, OTHER = 5;

UAchievementsManager::UAchievementsManager() {
	//Load Save game	
	UCubeTDSaveGame* LoadGameInstance = Cast<UCubeTDSaveGame>(UGameplayStatics::CreateSaveGameObject(UCubeTDSaveGame::StaticClass()));
	LoadGameInstance = Cast<UCubeTDSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	
	if (IsValid(LoadGameInstance)) {
		Achievements = LoadGameInstance->Achievements;
	}
	if(Achievements.Num()==0){
		CreateAchievements();
	}
}

void UAchievementsManager::UpdateAchievements(const FCubeTDStats &Stats, uint8 Type)
{
	if (Type == ENEMIES || Type == ALL) {
		UpdateAchievementProgression(ENEMIES1NAME, ENEMIES1NUM, Stats.EnemiesKilled);
		UpdateAchievementProgression(ENEMIES2NAME, ENEMIES2NUM, Stats.EnemiesKilled);
		UpdateAchievementProgression(ENEMIES3NAME, ENEMIES3NUM, Stats.EnemiesKilled);
		UpdateAchievementProgression(ENEMIES4NAME, ENEMIES4NUM, Stats.EnemiesKilled);
	}
	if (Type == TOWERS || Type == ALL) {
		UpdateAchievementProgression(TOWERS1NAME, TOWERS1NUM, Stats.TowersBuilt);
		UpdateAchievementProgression(TOWERS2NAME, TOWERS2NUM, Stats.TowersBuilt);
		UpdateAchievementProgression(TOWERS3NAME, TOWERS3NUM, Stats.TowersBuilt);
		UpdateAchievementProgression(TOWERS4NAME, TOWERS4NUM, Stats.TowersBuilt);
	}
	if (Type == RESOURCES || Type == ALL) {
		UpdateAchievementProgression(RESOURCES1NAME, RESOURCES1NUM, Stats.ResourcesGained);
		UpdateAchievementProgression(RESOURCES2NAME, RESOURCES2NUM, Stats.ResourcesGained);
		UpdateAchievementProgression(RESOURCES3NAME, RESOURCES3NUM, Stats.ResourcesGained);
	}
	if (Type == ROUNDS || Type == ALL) {
		UpdateAchievementProgression(ROUNDS1NAME, ROUNDS1NUM, Stats.RoundsWon);
		UpdateAchievementProgression(ROUNDS2NAME, ROUNDS2NUM, Stats.RoundsWon);
		UpdateAchievementProgression(ROUNDS3NAME, ROUNDS3NUM, Stats.RoundsWon);
		UpdateAchievementProgression(ROUNDS4NAME, ROUNDS4NUM, Stats.RoundsWon);
	}
	if (Type == OTHER || Type == ALL) {
		UpdateAchievementProgression(MAZE1NAME, MAZE1NUM, Stats.MazeLenght);
	}
}


void UAchievementsManager::CleanAchievements()
{
	Achievements.Empty();
}

void UAchievementsManager::ResetAchievements()
{
	CleanAchievements();
	CreateAchievements();
}

void UAchievementsManager::UpdateAchievementProgression(const FString Name, const float Threshold, const float Value)
{
	auto Achievement = Achievements.Find(Name);
	if (!Achievement->Obtained) {
		if (Value >= Threshold) {
			Achievement->Progression = 1;
			Achievement->Obtained = true;
			OnAchievementObtained.Broadcast(*Achievement);
		}
		else {
			Achievement->Progression = Value / Threshold;
		}
	}
}

void UAchievementsManager::CreateAchievements()
{
	//Hard coded Achievements... sorry
	//Enemies Achievements
	Achievements.Add(ENEMIES1NAME, FAchievement(ENEMIES1NAME));
	Achievements.Add(ENEMIES2NAME, FAchievement(ENEMIES2NAME));
	Achievements.Add(ENEMIES3NAME, FAchievement(ENEMIES3NAME));
	Achievements.Add(ENEMIES4NAME, FAchievement(ENEMIES4NAME));

	//Towers Achievements
	Achievements.Add(TOWERS1NAME, FAchievement(TOWERS1NAME));
	Achievements.Add(TOWERS2NAME, FAchievement(TOWERS2NAME));
	Achievements.Add(TOWERS3NAME, FAchievement(TOWERS3NAME));
	Achievements.Add(TOWERS4NAME, FAchievement(TOWERS4NAME));

	//Resources Achievements
	Achievements.Add(RESOURCES1NAME, FAchievement(RESOURCES1NAME));
	Achievements.Add(RESOURCES2NAME, FAchievement(RESOURCES2NAME));
	Achievements.Add(RESOURCES3NAME, FAchievement(RESOURCES3NAME));

	//Rounds Achievements
	Achievements.Add(ROUNDS1NAME, FAchievement(ROUNDS1NAME));
	Achievements.Add(ROUNDS2NAME, FAchievement(ROUNDS2NAME));
	Achievements.Add(ROUNDS3NAME, FAchievement(ROUNDS3NAME));
	Achievements.Add(ROUNDS4NAME, FAchievement(ROUNDS4NAME));

	//Other Achievements
	Achievements.Add(MAZE1NAME, FAchievement(MAZE1NAME));
}
