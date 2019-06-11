// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/StaticMeshComponent.h"

#include "GameFramework/Actor.h"
#include "CubeTDBox.generated.h"

UCLASS()
class CUBETD_API ACubeTDBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACubeTDBox();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Navigable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Interactionable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FIntVector Position;

	UFUNCTION()
	bool IsNavigable() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
