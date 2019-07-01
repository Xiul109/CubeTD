// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicStructure.h"
#include "Nexus.generated.h"

/**
 * 
 */
UCLASS()
class CUBETD_API ANexus : public ABasicStructure
{
	GENERATED_BODY()

		DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDamageDoneDelegate, float, DamageDone, float, CurrentLife);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxLife;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentLife;

	UPROPERTY(BlueprintAssignable)
	FDamageDoneDelegate OnDamageDone;
public:
	virtual void OnConstruction(const FTransform & Transform) override;

	UFUNCTION(BlueprintCallable)
	void ApplyDamage(float Damage);
	
protected:
	UFUNCTION()
	void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	virtual void BeginPlay() override;
};