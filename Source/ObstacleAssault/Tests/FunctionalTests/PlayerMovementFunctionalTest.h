// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "PlayerMovementFunctionalTest.generated.h"

/**
 * 
 */
UCLASS()
class OBSTACLEASSAULT_API APlayerMovementFunctionalTest : public AFunctionalTest
{
	GENERATED_BODY()
	
private:

	/* Reference of main player */
	UPROPERTY(EditAnywhere)
	class ACharacter* Player;

	/* Initial location of the player */
	FVector InitialLocation;

protected:

	virtual void BeginPlay() override;

	/* Total movement distance */
	UPROPERTY(EditAnywhere)
	float MovementDistance = 250.f;

	/* Distance threshold in order to get for target location */
	UPROPERTY(EditAnywhere)
	float DistanceThreshold=55.f;

public:

	virtual void Tick(float DeltaSeconds) override;

	/**
	 * Returns true when the player has traveled MovementDistance - DistanceThreshold
	 */
	bool TraveledTotalDistance() const;
	
};