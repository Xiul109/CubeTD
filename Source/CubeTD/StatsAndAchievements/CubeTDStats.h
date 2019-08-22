#pragma once

#include "CoreMinimal.h"
#include "CubeTDStats.generated.h"

USTRUCT(BlueprintType)
struct CUBETD_API FCubeTDStats {
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int EnemiesKilled;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int TowersBuilt;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int ResourcesGained;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int MazeLenght;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int RoundsWon;

	FCubeTDStats() {
		EnemiesKilled = 0;
		TowersBuilt = 0;
		ResourcesGained = 0;
		MazeLenght = 0;
		RoundsWon = 0;
	}
};