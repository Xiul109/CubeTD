// Fill out your copyright notice in the Description page of Project Settings.

#include "CubeTDGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "StatsAndAchievements/CubeTDSaveGame.h"


UCubeTDGameInstance::UCubeTDGameInstance() {
	AchievementsManager = NewObject<UAchievementsManager>();

	UCubeTDSaveGame* LoadGameInstance = Cast<UCubeTDSaveGame>(UGameplayStatics::CreateSaveGameObject(UCubeTDSaveGame::StaticClass()));
	LoadGameInstance = Cast<UCubeTDSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));

	if (IsValid(LoadGameInstance)) {
		Stats = LoadGameInstance->Stats;
		Names = LoadGameInstance->Names;
	}
}

void UCubeTDGameInstance::CleanStats()
{
	Stats.Empty();
	Names.Empty();
}

void UCubeTDGameInstance::BeginDestroy()
{
	Super::BeginDestroy();

	UCubeTDSaveGame* SaveGameInstance = Cast<UCubeTDSaveGame>(UGameplayStatics::CreateSaveGameObject(UCubeTDSaveGame::StaticClass()));
	SaveGameInstance->Stats = Stats;
	SaveGameInstance->Names = Names;
	SaveGameInstance->Achievements = AchievementsManager->Achievements;
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
}

void UCubeTDGameInstance::EraseGameData()
{
	UCubeTDSaveGame* SaveGameInstance = Cast<UCubeTDSaveGame>(UGameplayStatics::CreateSaveGameObject(UCubeTDSaveGame::StaticClass()));
	UGameplayStatics::DeleteGameInSlot(SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);

	CleanStats();
	AchievementsManager->ResetAchievements();
}
