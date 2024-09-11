#include "CoreMinimal.h" 
#include "GameFramework/Actor.h" 
#include "ObstacleAssault/MovingPlatform.h" 
#include "Misc/AutomationTest.h" 
#include "Tests/AutomationEditorCommon.h" 

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMovingPlatformMovementTest, "ObstacleAssault.MovingPlatform.MovementTest", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FMovingPlatformMovementTest::RunTest(const FString& Parameters)
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
    float TestDistance = 500.0f;
    FVector TestVelocity(100, 0, 0);
    FRotator TestRotation(0, 0, 0);
    
    // Initialize the platform with the test parameters
    Platform->InitializePlatform(InitialLocation, TestDistance, TestVelocity, TestRotation);

    // Simulate movement
    const float DeltaTime = 1.0f;
    Platform->Tick(DeltaTime); 
    
    // Check if the actual location of the platform matches the expected location
    FVector ExpectedLocation = InitialLocation + (TestVelocity * DeltaTime);
    if (!Platform->GetCurrentLocation().Equals(ExpectedLocation, KINDA_SMALL_NUMBER))
    {
        FString ErrorMessage = FString::Printf(TEXT("Platform did not move to the expected location. Expected: %s, Actual: %s"), *ExpectedLocation.ToString(), *Platform->GetCurrentLocation().ToString());
        AddError(*ErrorMessage);
        return false;
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMovingPlatformDirectionChangeTest, "ObstacleAssault.MovingPlatform.DirectionChange", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FMovingPlatformDirectionChangeTest::RunTest(const FString& Parameters)
{
    // Create a new world for testing
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

    // Initialize the platform with the test parameters
    FVector InitialLocation(0, 0, 0); 
    float TestDistance = 500.0f;
    FVector TestVelocity(100, 0, 0); 
    FRotator TestRotation(0,0,0);
    Platform->InitializePlatform(InitialLocation, TestDistance, TestVelocity, TestRotation);

    // Determine how long it should take to reach the move distance
    float RequiredTime = TestDistance / TestVelocity.Size();
    const float DeltaTime = 1.0f;

    // Simulate movement until the platform should start reversing direction
    for (int i = 0; i < RequiredTime; i++)
    {
        Platform->Tick(DeltaTime);
    }

    // Verify that the platform has reached the end of its movement
    FVector ExpectedLocation = InitialLocation + (TestVelocity * RequiredTime);
    if (!Platform->GetCurrentLocation().Equals(ExpectedLocation, KINDA_SMALL_NUMBER))
    {
        FString ErrorMessage = FString::Printf(TEXT("Platform did not reach the expected location. Expected: %s, Actual: %s"), *ExpectedLocation.ToString(), *Platform->GetCurrentLocation().ToString());
        AddError(*ErrorMessage);
        return false;
    }

    // Continue simulation to check if the platform reverses direction and returns to the start position
    for (int i = 0; i < RequiredTime + 1; i++)
    {
        Platform->Tick(DeltaTime);
    }

    // Verify that the platform has returned to the start location
    if (!Platform->GetCurrentLocation().Equals(InitialLocation, KINDA_SMALL_NUMBER))
    {
        FString ErrorMessage = FString::Printf(TEXT("Platform did not return to the start location. Expected: %s, Actual: %s"), *InitialLocation.ToString(), *Platform->GetCurrentLocation().ToString());
        AddError(*ErrorMessage);
        return false;
    }

    return true;
}