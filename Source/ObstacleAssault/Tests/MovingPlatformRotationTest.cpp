#include "CoreMinimal.h" 
#include "GameFramework/Actor.h" 
#include "ObstacleAssault/MovingPlatform.h" 
#include "Misc/AutomationTest.h" 
#include "Tests/AutomationEditorCommon.h" 

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMovingPlatformRotationTest, "ObstacleAssault.MovingPlatform.RotationTest", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FMovingPlatformRotationTest::RunTest(const FString& Parameters)
{
    // Create a new map (world) for testing
    UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
    if (!World)
    {
        AddError(TEXT("World is not available"));
        return false;
    }

    // Spawn an instance of AMovingPlatform in the world
    AMovingPlatform* Platform = World->SpawnActor<AMovingPlatform>();
    if (!Platform)
    {
        AddError(TEXT("Failed to spawn MovingPlatform actor"));
        return false;
    }

    // Set initial parameters for the MovingPlatform
    FVector InitialLocation(0, 0, 0);
    float TestDistance = 0.f;
    FVector TestVelocity(0, 0, 0);
    FRotator TestRotation(0, 0, 100);
    
    // Initialize the platform with the test parameters
    Platform->InitializePlatform(InitialLocation, TestDistance, TestVelocity, TestRotation);

    // Simulate rotation
    const float DeltaTime = 1.0f;
    Platform->Tick(DeltaTime); 
    
    // Check if the actual rotation of the platform matches the expected rotation
    FRotator ExpectedRotation =  TestRotation * DeltaTime;
    if (!Platform->GetCurrentRotation().Equals(ExpectedRotation, KINDA_SMALL_NUMBER))
    {
        FString ErrorMessage = FString::Printf(TEXT("Platform did not rotate to the expected rotation. Expected: %s, Actual: %s"), *ExpectedRotation.ToString(), *Platform->GetCurrentRotation().ToString());
        AddError(*ErrorMessage);
        return false;
    }


    return true;
}