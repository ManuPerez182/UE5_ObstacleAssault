# Obstacle Assault

This repository contains a simple game developed using Unreal Engine 5, based on the course [Unreal Engine 5 C++ Developer: Learn C++ & Make Video Games](https://www.udemy.com/course/unrealcourse/).
The goal of the game is to navigate through a series of obstacles such as rising and falling platforms, pushing cubes, and rotating platforms to reach the treasure located within the castle.

![ObstacleAssaultPhoto](https://github.com/user-attachments/assets/a578244d-2574-40b1-9eb9-371de12cd824)

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

## [Unit Tests](https://github.com/ManuPerez182/UE5_ObstacleAssault/tree/main/Source/ObstacleAssault/Tests)

A unit test is a type of automated test that focuses on verifying the functionality of a small, isolated piece of code—typically a single function or method—within a larger software system. In Unreal Engine, unit tests are used to ensure that individual components, such as classes or functions, behave as expected under various conditions. These tests are written and executed in isolation from other parts of the system to confirm that they produce the correct results and handle edge cases appropriately.

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

In addition to the unit test cases implemented in Unreal Engine, I have also developed three functional test cases using Functional Test Blueprints. These test cases are designed to verify the correct interaction of various obstacles with the player. The specific obstacles tested include:

- **Moving Platforms:** These platforms move along a predefined path and are tested to ensure that the player correctly interacts with them both in terms of standing on them and being moved by them.

- **Rotating Platforms:** These platforms rotate around an axis, and the test ensures that the player interacts correctly with these rotating surfaces.

- **Pushing Cubes:** These cubes push the player when in contact. The test verifies that the player is correctly affected by the pushing cube and that the interaction behaves as expected.

https://github.com/user-attachments/assets/f7494528-9653-484d-9959-b5dd8e9592f9

