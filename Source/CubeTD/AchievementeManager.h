// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AchievementeManager.generated.h"

USTRUCT(BlueprintType)
struct CUBETD_API FAchievement {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString Name;
	UPROPERTY(BlueprintReadOnly)
	float Progression;
	UPROPERTY(BlueprintReadOnly)
	bool Obtained;

	FAchievement() {
		Name = "Achievement",
		Progression = 0;
		Obtained = false;
	}
};

/**
 * 
 */
UCLASS()
class CUBETD_API UAchievementeManager : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	TArray<FAchievement> AchievementsList;
	
	
};
