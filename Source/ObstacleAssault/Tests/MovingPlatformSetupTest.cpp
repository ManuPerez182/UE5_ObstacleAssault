#include "ObstacleAssault/MovingPlatform.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMovingPlatformInitialSetupTest, "ObstacleAssault.MovingPlatform.InitialSetup", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FMovingPlatformInitialSetupTest::RunTest(const FString& Parameters)
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

    // Check default property values
    if (!Platform->GetPlatformVelocity().Equals(FVector(0, 0, 0), KINDA_SMALL_NUMBER))
    {
        AddError(TEXT("PlatformVelocity is not set to default value"));
        return false;
    }

    if (!FMath::IsNearlyEqual(Platform->GetMoveDistance(), 0.f, KINDA_SMALL_NUMBER))
    {
        AddError(TEXT("MoveDistance is not set to default value"));
        return false;
    }

    if (!Platform->GetRotationVelocity().Equals(FRotator(0, 0, 0), KINDA_SMALL_NUMBER))
    {
        AddError(TEXT("RotationVelocity is not set to default value"));
        return false;
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMovingPlatformInitialPositionTest, "ObstacleAssault.MovingPlatform.InitialPosition", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FMovingPlatformInitialPositionTest::RunTest(const FString& Parameters)
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

    // Store the initial position of the platform
    FVector InitialLocation = Platform->GetActorLocation();

    // Simulate a short time to ensure the platform has not moved
    const float DeltaTime = 0.1f;
    Platform->Tick(DeltaTime);

    // Verify that the platform is at the initial location
    if (Platform->GetActorLocation() != InitialLocation)
    {
        AddError(TEXT("Platform has moved from its initial position unexpectedly"));
        return false;
    }

    return true;
}