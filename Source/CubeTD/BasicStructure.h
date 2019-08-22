// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BasicStructure.generated.h"

UCLASS()
class CUBETD_API ABasicStructure : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicStructure();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Navigable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StructureDamage")
	float ProjectileDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StructureDamage")
	float ProjectileDamageUpgrade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Name")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy")
	int BaseCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy")
	int UpgradeCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StructureDamage")
	int Level;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		float GetDamage();
	UFUNCTION(BlueprintCallable)
		float GetDamageUpdate();
	UFUNCTION(BlueprintCallable)
		FString GetName();
	
	UFUNCTION(BlueprintCallable, Category = "Economy")
		virtual int CalcUpgradeCost();

	UFUNCTION(BlueprintCallable)
	int GetLevel();
};
