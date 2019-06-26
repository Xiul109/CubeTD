// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/StaticMeshComponent.h"

#include "GameFramework/Actor.h"
#include "BasicTower.h"
#include "ShootingTower.h"
#include "CubeTDBox.generated.h"


UCLASS()
class CUBETD_API ACubeTDBox : public AActor
{
	GENERATED_BODY()

		DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBoxDelegate, ACubeTDBox*, Box);

public:
	// Sets default values for this actor's properties
	ACubeTDBox();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* DefaultMaterial;
	UPROPERTY(EditAnywhere)
		UMaterialInterface* HoverMaterial;
	UPROPERTY(EditAnywhere)
		UMaterialInterface* UsedMaterial;
	UPROPERTY(EditAnywhere)
		UMaterialInterface* ErrorMaterial;

	UPROPERTY()
		ABasicTower* Tower;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arena Settings")
		TSubclassOf<ABasicTower> BasicTowerClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arena Settings")
		TSubclassOf<ABasicTower> ShootingTowerClass;



	//Navigation Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Navigable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool ContainsStructure;

	//UI Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		bool Interactionable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		bool Selected;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FIntVector Position;

	//Delegates
	FBoxDelegate OnBoxPreUpdated;
	FBoxDelegate OnBoxSelected;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Functions for delegates
	UFUNCTION()
		void OnBeginMouseOver(UPrimitiveComponent* TouchedComponent);
	UFUNCTION()
		void OnEndMouseOver(UPrimitiveComponent* TouchedComponent);
	UFUNCTION()
		void OnMouseClicked(UPrimitiveComponent* TouchedComponent, FKey Key);
	//Hidden attributes
	bool NeedsUpdate;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		bool IsNavigable() const;

	UFUNCTION(BlueprintCallable)
		void DestroyStructure();
	UFUNCTION(BlueprintCallable)
		void BuildStructure();
	UFUNCTION(BlueprintCallable)
		void UpgradeStructure();

	UFUNCTION(BlueprintCallable)
		void UpdateBox();
	UFUNCTION(BlueprintCallable)
		void CancelUpdate();
};