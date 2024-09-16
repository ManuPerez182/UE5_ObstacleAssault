#include "CoreMinimal.h" 
#include "GameFramework/Actor.h" 
#include "ObstacleAssault/MovingPlatform.h" 
#include "Misc/AutomationTest.h" 
#include "Tests/AutomationEditorCommon.h" 

DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FSetupMovingPlatform, 
AMovingPlatform*, Platform,
const FVector, InitialLocation,
const float, TestDistance,
const FVector, TestVelocity,
const FRotator, TestRotation);
bool FSetupMovingPlatform::Update()
{
    if (!Platform)
    {
        return true;
    }
   
   // Initialize the platform with the test parameters
    Platform->InitializePlatform(InitialLocation, TestDistance, TestVelocity, TestRotation);

    return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FSimulatePlatformMovement, AMovingPlatform*, Platform, float, DeltaTime, float, RequiredTime, FAutomationTestBase*, Test);

bool FSimulatePlatformMovement::Update()
{
    static float CurrentTime = 0.0f;

    if (!Platform)
    {
        Test->AddError(TEXT("MovingPlatform is not available"));
        return true;
    }
    
    // Increment Current Time and perform a tick
    CurrentTime += DeltaTime;
    Platform->Tick(DeltaTime);

    if (CurrentTime >= RequiredTime)
    {
        CurrentTime = 0.0f; 
        return true;
    } 

    // Continue waiting until the required time is complete
    return false; 
}
DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckPlatformMovement, AMovingPlatform*, Platform, const FVector, ExpectedLocation, FAutomationTestBase*, Test);
bool FCheckPlatformMovement::Update()
{
    if (!Platform)
    {
        return true;
    }

    // Check if the actual location of the platform matches the expected location
    Test->TestTrue(TEXT("that the platform moved to expected location"),  Platform->GetCurrentLocation().Equals(ExpectedLocation, KINDA_SMALL_NUMBER));
    return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMovingPlatformMovementTest, "ObstacleAssault.MovingPlatform.MovementTest", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FMovingPlatformMovementTest::RunTest(const FString& Parameters)
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

    // Test parameters
    FVector InitialLocation(0, 0, 0);
    float TestDistance = 500.0f;
    FVector TestVelocity(100, 0, 0);
    FRotator TestRotation(0, 0, 0);
    const float DeltaTime = 1.0f;
    
    // Initialize the platform with the test parameters
    Platform->InitializePlatform(InitialLocation, TestDistance, TestVelocity, TestRotation);

    // Simulate movement
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

    // Test parameters
    FVector InitialLocation(0, 0, 0); 
    float TestDistance = 500.0f;
    FVector TestVelocity(100, 0, 0); 
    FRotator TestRotation(0,0,0);
    Platform->InitializePlatform(InitialLocation, TestDistance, TestVelocity, TestRotation);
    const float DeltaTime = 1.0f;

    // Determine the expected location and how long it should take to reach it
    float RequiredTime = TestDistance / TestVelocity.Size();
    FVector ExpectedLocation = InitialLocation + (TestVelocity * RequiredTime);

    // Simulate movement until the platform should start reversing direction
    for (int i = 0; i < RequiredTime; i++)
    {
        Platform->Tick(DeltaTime);
    }

    // Verify that the platform has reached the end of its movement 
    if (!Platform->GetCurrentLocation().Equals(ExpectedLocation, KINDA_SMALL_NUMBER))
    {
        FString ErrorMessage = FString::Printf(TEXT("Platform did not reach the expected location. Expected: %s, Actual: %s"), *ExpectedLocation.ToString(), *Platform->GetCurrentLocation().ToString());
        AddError(*ErrorMessage);
        return false;
    }

    // Continue simulation to check if the platform reverses direction and returns to the start position
    // Note: An extra iteration is required because when the platform first reaches or exceeds the MoveDistance,just inverts its velocity.
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

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMovingPlatformMovementTestWithLatentCommands, "ObstacleAssault.MovingPlatform.MovementTestWithLatentCommands", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FMovingPlatformMovementTestWithLatentCommands::RunTest(const FString& Parameters)
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

    // Test parameters
    FVector InitialLocation(0, 0, 0);
    float TestDistance = 500.0f;
    FVector TestVelocity(100, 0, 0);
    FRotator TestRotation(0, 0, 0);
    const float DeltaTime = 1.0f;

    // Determine the expected location and how long it should take to reach it
    float RequiredTime = TestDistance / TestVelocity.Size();
    FVector ExpectedLocation = InitialLocation + (TestVelocity * RequiredTime);

    ADD_LATENT_AUTOMATION_COMMAND(FSetupMovingPlatform(Platform, InitialLocation, TestDistance, TestVelocity, TestRotation));
    ADD_LATENT_AUTOMATION_COMMAND(FSimulatePlatformMovement(Platform, DeltaTime, RequiredTime, this));
    ADD_LATENT_AUTOMATION_COMMAND(FCheckPlatformMovement(Platform, ExpectedLocation, this));

    return true;
}