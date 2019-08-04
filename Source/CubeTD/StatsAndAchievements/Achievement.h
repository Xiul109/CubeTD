#pragma once

#include "CoreMinimal.h"
#include "Achievement.generated.h"

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

	FAchievement(FString AchievementName) {
		Name = AchievementName,
			Progression = 0;
		Obtained = false;
	}
};