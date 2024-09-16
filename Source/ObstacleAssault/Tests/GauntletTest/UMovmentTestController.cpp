#include "UMovmentTestController.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMovmentGauntletTestController::OnPostMapChange(UWorld* World)
{
    if (World)
    {
        // Check if the current map is the expected map
        if (World->GetMapName() != TestMapName.ToString())
        {
            // Change the map to the expected one
            UGameplayStatics::OpenLevel(World, TestMapName);

            // Set the test state to WaitingForMapChange
            MarkHeartbeatActive(FString("Changing map to the expected one."));
            return;
        }

        // Use GetFirstPlayerController to find the player
        APlayerController* PlayerController = GetFirstPlayerController();
        if (PlayerController)
        {
            Player = Cast<ACharacter>(PlayerController->GetPawn());
            if (Player)
            {
                // Store the initial location of the player
                InitialLocation = Player->GetActorLocation();

                // Begin the test
                MarkHeartbeatActive(FString("Test started. Moving the player."));
                return;
            }
        }
        return;
    }
}

bool UMovmentGauntletTestController::TraveledTotalDistance() const
{
    if (Player)
    {
        float DistanceTraveled = FVector::Dist(InitialLocation, Player->GetActorLocation());
        return DistanceTraveled > (MovementDistance - DistanceThreshold);
    }
    return false;
}

void UMovmentGauntletTestController::OnTick(float DeltaSeconds)
{
    Super::OnTick(DeltaSeconds);

    // Check if the map has changed to the expected one
    if (GetWorld() && GetWorld()->GetMapName() == TestMapName.ToString())
    {
        // Check if the player has traveled the required distance
        if (TraveledTotalDistance())
        {
            // Finish the test successfully
            MarkHeartbeatActive(FString("SUCCESS: Traveled required units!"));
            EndTest(0);
        }
    }
    else
    {
        // If the map is not as expected, continue to wait for the correct map to load
        MarkHeartbeatActive(FString("Waiting for correct map to load."));
    }
}
