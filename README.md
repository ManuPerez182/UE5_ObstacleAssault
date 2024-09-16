# Obstacle Assault

This repository contains a simple game developed using Unreal Engine 5, based on the course [Unreal Engine 5 C++ Developer: Learn C++ & Make Video Games](https://www.udemy.com/course/unrealcourse/).
The goal of the game is to navigate through a series of obstacles such as rising and falling platforms, pushing cubes, and rotating platforms to reach the treasure located within the castle.

![Capture](https://github.com/user-attachments/assets/c1e316ae-d714-4c63-a1c6-b6745acd905b)


### Controls
- **W, A, S, D:** Move
- **Spacebar:** Jump

By using this game, I aim to create and implement automated test cases to better understand and develop testing strategies within Unreal Engine 5.

## Moving Platform

The `AMovingPlatform` class represents a moving platform in Unreal Engine 5. It extends from the `AActor` class and provides functionality for both movement and rotation.

### Features

- **Movement:** The platform moves along a specified direction with a velocity defined by PlatformVelocity. It moves a certain distance before returning to its starting position.
- **Rotation:** The platform can rotate based on the RotationVelocity property.
- **Movement Management:** Includes methods for moving and rotating the platform, checking if the platform should return to its start position, and calculating the distance moved.

### Properties:

- **PlatformVelocity:** Controls the speed and direction of the platform movement.
- **MoveDistance:** Defines how far the platform moves before reversing direction.
- **RotationVelocity:** Specifies the rotational speed of the platform.

The class is designed to handle basic platform movement and rotation logic, providing a foundation for more complex interactions and behaviors.

# Testing Frameworks in Unreal Engine

Unreal Engine offers two primary testing frameworks: **Functional Tests** and **Gauntlet**. Here's a summary of their key features and differences:

### Functional Tests

- **Usage:** Ideal for small unit tests and larger integration tests.
- **Execution:** Can be run both in the Unreal Editor and from the command line.
- **Limitations:** Primarily designed for use within the editor and does not support performance testing or full builds.
- **Platform Support:** Limited to the development environment and may not cover all target platforms.

### Gauntlet

- **Usage:** Designed for comprehensive gameplay testing and performance evaluation.
- **Execution:** Requires a full build and runs outside the Unreal Editor.
- **Platform Support:** Can be used across various platforms including PC, console, and mobile.
- **Advantages:** Ideal for performance testing, including FPS measurements and detecting performance drops.


Functional Tests are best for testing individual units and smaller integrations directly within the editor. They are versatile and easy to use for immediate feedback.
Gauntlet is more suited for end-to-end gameplay testing, particularly when evaluating performance on different platforms. It’s ideal for scenarios where you need to measure real-world performance and behavior.

# Functional Tests Framework

## [Unit Test](https://github.com/ManuPerez182/UE5_ObstacleAssault/tree/main/Source/ObstacleAssault/Tests)

A unit test is a type of automated test that focuses on verifying the functionality of a small, isolated piece of code typically a single function or method within a larger software system.
In Unreal Engine, unit tests are used to ensure that individual components, such as classes or functions, behave as expected under various conditions. These tests are written and executed in isolation from other parts of the system to confirm that they produce the correct results and handle edge cases appropriately.

### Setup Tests

**Test Case:** Verify Default Property Initialization

- **Objective:** Ensure that the default values for PlatformVelocity, MoveDistance, and RotationVelocity are initialized correctly when a new instance of AMovingPlatform is created.
- **Description:** Create an instance of the AMovingPlatform class and verify that the properties PlatformVelocity, MoveDistance, and RotationVelocity are set to their default values as specified in the class definition.

**Test Case:** Verify Initial Position

- **Objective:** Ensure that the platform starts at the correct initial location.
- **Description:** Create an instance of the AMovingPlatform class and record the initial position of the platform. Simulate a short time and verify that the platform starts at the recorded initial location before any movement occurs.

### Movement Tests

**Test Case:** Verify Platform Movement

- **Objective:** Ensure that the platform moves correctly according to the PlatformVelocity and MoveDistance properties.
- **Description:** Create an instance of the AMovingPlatform class with a specified PlatformVelocity and MoveDistance.
Simulate the platform's movement over time and verify that the platform moves the expected distance.
This test case is implemented in two ways:
    - **With LATENT_AUTOMATION_COMMANDS:** Latent Commands can be queued up during RunTest, causing sections of the code to run across multiple frames.This version of the test uses latent commands to handle asynchronous operations, allowing for more reliable simulation and validation of the platform’s movement over time.
    - **Without LATENT_AUTOMATION_COMMANDS:** Uses a synchronous approach, manually simulating movement and validating results immediately, which may be less accurate in handling time based operations.

**Test Case:** Verify Platform Direction Change

- **Objective**: Ensure that the platform changes direction correctly after reaching the defined movement distance.
- **Description:** Create an instance of the AMovingPlatform class and set a PlatformVelocity and MoveDistance.
Simulate enough movement time to reach the MoveDistance and check if the platform's direction reverses as expected and moves back to the start position.

### Rotation Tests

**Test Case:** Verify Platform Rotation

- **Objective:** Ensure that the platform rotates correctly according to the RotationVelocity property.
- **Description:** Create an instance of the AMovingPlatform class with a specified RotationVelocity.
Simulate rotation over time and verify that the platform's rotation updates correctly according to the RotationVelocity.

## Functional Test

A functional test is a type of automated test designed to verify that specific game features or mechanics work as intended from the player’s perspective. Unlike unit tests, which focus on individual components or pieces of code, functional tests evaluate the behavior of the game as a whole, ensuring that various elements interact correctly and meet design specifications.

In addition to the unit test cases implemented in Unreal Engine, I have also developed three functional test cases using the Unreal functional test framework. These test cases are designed to verify the correct interaction of various obstacles with the player. The specific obstacles tested include:

**Test Case:** Verify Moving Platforms Interaction

- **Objective:** Ensure that the player character correctly interacts with moving platforms.

- **Description:** Verify that the player remains correctly positioned on the platform and that the platform's movement is accurately reflected in the player's position.

**Test Case:** Verify Rotating Platforms Interaction

- **Objective:** Ensure that the player character interacts correctly with rotating platforms, including standing on and rotating.

- **Description:** Verify that the player's interaction with the rotating surface behaves as expected, such as maintaining relative orientation and not falling off or getting stuck.

**Test Case:** Verify Pushing Cubes Interaction

- **Objective:** Ensure that the player character is correctly affected by pushing cubes when in contact with them.

- **Description:** Simulate the interaction to verify that the pushing cube applies force to the player character, causing it to move as expected. Check that the interaction correctly influences the player's movement and that the behavior of the pushing cube aligns with the expected physical interactions.

Besides the functional tests I created using Blueprints, I have also developed a test using C++ to illustrate how such testing can be conducted without relying on Blueprints.

- **Test Case:** Verify Player Movement

    - **Objective:** Ensure that the player character moves correctly according to the MovementDistance and DistanceThreshold properties.
    - **Description:** Create an instance of the APlayerMovementFunctionalTest class with a specified MovementDistance and DistanceThreshold. Simulate the player's movement over time and verify that the player travels the expected distance.

https://github.com/user-attachments/assets/daa68452-0406-4150-97d6-704f06beb4ab

# Gauntlet Automation Framework

## Unreal Automation Tool

The Unreal Engine includes a tool called Unreal AutomationTool or 'UAT' for short. UAT is written in C# and is a collection of various tools that can be used to compile code, cook content and package your game (among other things).
`BuildCookRun` is used to compile your game code, cook content, and stage the cooked content as a packaged format. Packaging your game is the most efficient method of distributing your game to other people for them to play.

```
RunUAT BuildCookRun -project=<ProjectPath> -platform=<Platform> -configuration=<Configuration> -build -cook -pak -stage -clean
```

- **clean:** Deletes intermediate files (like source code object files) and cleans (deletes) the previous cooked or staged (packaged) files before the packaging process starts.

- **build:** If you have a C++ project, this will allow the packaging tool to build your source code to create the standalone executables used to load and run cooked content.

- **cook:** Tells the AutomationTool to cook the game content for packaging. Cooking removes data in the Unreal .uasset packages that is only needed in the editor, so cooking makes the assets a little smaller. Cooking will also build shaders for any content that has shaders that are out of date.

- **stage:** This tells the AutomationTool to stage the cooked content for packaging. Staging the game also adds the game executable to the packaged format and can include the Epic Prerequisite installer (which installs DirectX and C runtime libraries if needed).

- **platform:** The platform that you want to package for. For Windows this would typically be "Win64" for 64-bit Windows operating systems.

- **configuration:** Indicates which "build configuration" you want to use, which identifies which game executable will be included in the packaged build.

- **pak:** This tells the packaging tool to put all of the cooked content into Unreal Engine .pak files, which can be compressed. 

## Gauntlet

The Gauntlet testing framework is designed for testing cooked games, offering robust tools for collecting profiling data and executing tests across various platforms. It integrates seamlessly with Continuous Integration (CI) tools such as Jenkins, simplifying the management of automated tests. The `RunUAT` utility is employed to initiate the game, allowing for configuration selection, platform specification, and test execution.

```
RunUAT RunUnreal -project=<ProjectPath> -platform=<Platform> -configuration=<Configuration> -build=<BuildDirectory> -execcmds=<Commands> -test=<TestName> -uploaddir=<UploadDirectory>
```

- **project:** Specifies the full path to the .uproject file.

- **platform:** Defines the platform on which to run the test.

- **configuration:** Indicates the configuration to use for the test run.

- **build:** Points to the directory where builds for all platforms are stored. Note that Gauntlet does not create builds but runs tests on pre existing builds.

- **execcmds:** Lists any commands to execute within the game, such as opening a specific map.

- **test:** Specifies the name of the Gauntlet test to be executed.

- **uploaddir:** Designates the directory for storing test output.

### Test Definition

The test is implemented as a C# class derived from DefaultTest. To create tests, a source build of the engine is required, and tests should be developed within a Class Library (.NET Framework). The project name should end with .Automation. The test code must utilize the GetConfiguration function to return the UnrealTestConfiguration. An essential parameter in the test definition is the name of the GauntletController to be used.

### GauntletController

The GauntletController is a class derived from UGauntletTestController, designed to manage the test execution while the game is running. It supports periodic updates through the Tick function and allows for test completion with the EndTest method.

### Gauntlet Test

**Test Case:** Verify Player Movement

- **Objective:** Ensure that the player character moves correctly according to the MovementDistance and DistanceThreshold properties.
- **Description:** Create an instance of the APlayerMovementFunctionalTest class with a specified MovementDistance and DistanceThreshold. Simulate the player's movement over time and verify that the player travels the expected distance.

https://github.com/user-attachments/assets/282ab645-8924-432a-97f2-a0727e290d58
