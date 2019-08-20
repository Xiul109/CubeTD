// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "BasicStructure.h"
#include "Blueprint/UserWidget.h"
#include "CubeTDGameStateBase.h"
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
	UPROPERTY(EditAnywhere)
		UMaterialInterface* DisabledMaterial;

	UPROPERTY()
		ABasicStructure* Structure;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arena Settings")
		TSubclassOf<ABasicStructure> BasicTowerClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arena Settings")
		TSubclassOf<ABasicStructure> ShootingTowerClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arena Settings")
		TSubclassOf<ABasicStructure> AoeTowerClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arena Settings")
		TSubclassOf<ABasicStructure> SlowTrapClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arena Settings")
		TSubclassOf<ABasicStructure> ExplosiveTrapClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD")
		TSubclassOf<UUserWidget> BuildHudClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD")
		TSubclassOf<UUserWidget> UpgradeTowerHudClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD")
		TSubclassOf<UUserWidget> UpgradeTowerStatsHudClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD")
		TSubclassOf<UUserWidget> TrapStatsHudClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UUserWidget* CurrentWidget;


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
	FBoxDelegate OnBoxDeselected;

	FBoxDelegate OnNotEnoughResources;

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
	void BuildStructure(int option);

	UFUNCTION(BlueprintCallable)
	void UpgradeStructure(int option);
	UFUNCTION(BlueprintCallable)
	void UpgradeTowerStats();
	UFUNCTION(BlueprintCallable)
	void UpdateBox();
	UFUNCTION(BlueprintCallable)
	void CancelUpdate();

	UFUNCTION(BlueprintCallable)
	void Disable();
	UFUNCTION(BlueprintCallable)
	void Enable();

	UFUNCTION(BlueprintCallable)
	void Select();
	UFUNCTION(BlueprintCallable)
	void Deselect();

	UFUNCTION(BlueprintCallable)
	ABasicStructure* GetStructure();
};