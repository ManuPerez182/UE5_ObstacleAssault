// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMovementFunctionalTest.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void APlayerMovementFunctionalTest::BeginPlay()
{
	Super::BeginPlay();

	if (Player)
	{
		InitialLocation = Player->GetActorLocation();
	}
}

void APlayerMovementFunctionalTest::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (Player)
	{
		//Go forward until we reach our destination
		Player->AddMovementInput(Player->GetActorForwardVector());
		if (TraveledTotalDistance())
		{
			FinishTest(EFunctionalTestResult::Succeeded,FString("Traveled required units!"));
		}
	}
	else
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Invalid player character!"));
	}
}

bool APlayerMovementFunctionalTest::TraveledTotalDistance() const
{
    if (Player)
    {
        float DistanceTraveled = FVector::Dist(InitialLocation, Player->GetActorLocation());
        return DistanceTraveled > DistanceThreshold;
    } 
    return false;
}