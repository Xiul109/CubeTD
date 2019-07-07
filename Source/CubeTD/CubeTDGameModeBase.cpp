// Fill out your copyright notice in the Description page of Project Settings.

#include "CubeTDGameModeBase.h"

#include "CubeTDGameStateBase.h"
#include "CubeTDPlayerController.h"

ACubeTDGameModeBase::ACubeTDGameModeBase() {
	PlayerControllerClass = ACubeTDPlayerController::StaticClass();
	GameStateClass = ACubeTDGameStateBase::StaticClass();
}

