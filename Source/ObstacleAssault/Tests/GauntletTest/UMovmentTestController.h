// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GauntletTestController.h"
#include "UMovmentTestController.generated.h"

/**
 * This Gauntlet controller tests the movement of the player
 */
UCLASS()
class OBSTACLEASSAULT_API UMovmentGauntletTestController : public UGauntletTestController
{
    GENERATED_BODY()

public:

    virtual void OnPostMapChange(UWorld* World) override;

protected:
    virtual void OnTick(float DeltaTime) override;

private:

    // Test map name
    UPROPERTY()
    FName TestMapName = "GauntletTestMap";

	// Total movement distance required
    UPROPERTY()
    float MovementDistance = 250.f;

    // Distance threshold
    UPROPERTY()
    float DistanceThreshold = 50.f;

    // Reference to the player character
    ACharacter* Player;

    // Initial location of the player
    FVector InitialLocation;

    // Check if the player has traveled the required distance
    bool TraveledTotalDistance() const;
};